/*
    GTool1CD provides GUI front end to Tool1CD library
    Copyright © 2009-2017 awa
    Copyright © 2017-2018 E8 Tools contributors

    This file is part of GTool1CD.

    GTool1CD is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    GTool1CD is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with GTool1CD.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "extensions_table_model.h"
#include <Class_1CD.h>

ExtensionsTableModel::ExtensionsTableModel(T_1CD *db):
    db(db)
{

}


int ExtensionsTableModel::rowCount(const QModelIndex &parent) const
{
	return db->supplier_configs().size();
}

int ExtensionsTableModel::columnCount(const QModelIndex &parent) const
{
	return 3;
}

QModelIndex ExtensionsTableModel::index(int row, int column, const QModelIndex &parent) const
{
	return QAbstractItemModel::createIndex(row, column);
}

QModelIndex ExtensionsTableModel::parent(const QModelIndex &child) const
{
	return QModelIndex();
}

QVariant ExtensionsTableModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid()) {
		return QVariant();
	}
	if (role == Qt::DisplayRole) {
	}

	return QVariant();
}

QVariant ExtensionsTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
		switch (section) {
		case 0:
			return tr("Конфигурация");
		case 1:
			return tr("Поставщик");
		case 2:
			return tr("Версия");
		}
	}
	return QVariant();
}
