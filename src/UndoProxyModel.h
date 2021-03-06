/* Copyright(C) 2016 Björn Stresing, Denis Manthey, Wolfgang Ruppel
 *
 * This program is free software : you can redistribute it and / or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once
#include <QIdentityProxyModel>
#include <QUndoCommand>
#include <QPointer>


class SetEditRoleDataCommand : public QUndoCommand {

public:
	SetEditRoleDataCommand(const QPersistentModelIndex &rModelIndex, const QString &rData, QUndoCommand *pParent = NULL);
	virtual ~SetEditRoleDataCommand() {}
	virtual void undo();
	//! Called ounce when pushed on Undo Stack.
	virtual void redo();

private:
	Q_DISABLE_COPY(SetEditRoleDataCommand);
	QString								mData;
	QString								mDataBackup;
	QPersistentModelIndex mModelIndex;
};


class UndoProxyModel : public QIdentityProxyModel {

	Q_OBJECT

public:
	UndoProxyModel(QUndoStack *pUndoStack = NULL, QObject *pParent = NULL);
	virtual ~UndoProxyModel() {}
	virtual bool setData(const QModelIndex &rIndex, const QVariant &rValue, int role = Qt::EditRole);
	void SetUndoStack(QUndoStack *pUndoStack);
	bool HasUndoStack() const { return mpUndoStack; }

private:
	Q_DISABLE_COPY(UndoProxyModel);

	QPointer<QUndoStack> mpUndoStack;
};
