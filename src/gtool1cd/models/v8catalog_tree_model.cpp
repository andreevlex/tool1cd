#include "v8catalog_tree_model.h"

V8CatalogTreeModel::V8CatalogTreeModel(V8Catalog *catalog, const QString &catalogName)
    : catalog(catalog), catalogName(catalogName)
{

}

int V8CatalogTreeModel::rowCount(const QModelIndex &parent) const
{
	if (parent.column() > 0) {
		return 0;
	}

	if (!parent.isValid()) {
		return 1;
	}

	V8File *parentItem = static_cast<V8File*>(parent.internalPointer());
	if (parentItem == nullptr) {
		return catalog->v8files().size();
	}
	if (parentItem->is_catalog()) {
		return parentItem->get_catalog()->v8files().size();
	}
	return 0;
}

int V8CatalogTreeModel::columnCount(const QModelIndex &parent) const
{
	return 1;
}

static V8File *get_file(V8Catalog *cat, int file_index)
{
	auto f = cat->get_first();
	while (file_index--) {
		if (f == nullptr) {
			return nullptr;
		}
		f = f->get_next();
	}
	return f;
}

QModelIndex V8CatalogTreeModel::index(int row, int column, const QModelIndex &parent) const
{
	if (!hasIndex(row, column, parent)) {
		return QModelIndex();
	}

	if (!parent.isValid()) {
		return createIndex(row, column, nullptr);
	}

	V8Catalog *parentItem = parent.internalPointer() == nullptr
	        ? catalog
	        : static_cast<V8File*>(parent.internalPointer())->get_catalog();
	V8File *childItem = get_file(parentItem, row);
	if (childItem == nullptr) {
		return QModelIndex();
	}
	return QAbstractItemModel::createIndex(row, column, childItem);
}


static int index_of(V8Catalog *parent, V8File *child)
{
	if (parent == nullptr) {
		return -1;
	}
	auto f = parent->get_first();
	for (int i = 0; f != nullptr; i++, f = f->get_next()) {
		if (f == child) {
			return i;
		}
	}
	return -1;
}


QModelIndex V8CatalogTreeModel::parent(const QModelIndex &child) const
{
	if (!child.isValid()) {
		return QModelIndex();
	}

	V8File *childItem = static_cast<V8File*>(child.internalPointer());
	if (childItem == nullptr) {
		return QModelIndex();
	}

	V8Catalog *parentItem = childItem->get_parent_catalog();
	if (parentItem == catalog) {
		return createIndex(0, 0, nullptr);
	}
	int parent_index = index_of(parentItem->get_parent_catalog(), parentItem->get_self_file());
	return createIndex(parent_index, 0, parentItem->get_self_file());
}

QVariant V8CatalogTreeModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid()) {
		return QVariant();
	}
	if (role == Qt::DisplayRole) {
		V8File *item = static_cast<V8File*>(index.internalPointer());
		switch (index.column()) {
		case 0:{
			if (item == nullptr) {
				return QString(catalogName);
			}
			return QString::fromStdString(item->get_file_name());
		}
		}
	}

	return QVariant();
}

QVariant V8CatalogTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
		switch (section) {
		case 0:
			return tr("Файл");
		}
	}
	return QVariant();
}