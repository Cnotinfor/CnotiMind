#ifndef DELETENOTE_H
#define DELETENOTE_H

#include "RuleNode.h"

namespace CnotiMind
{

	class DeleteNote : public RuleNode
	{
		Q_OBJECT
	public:
		explicit DeleteNote(const QString& key, const QString& value, DataMiningOperation dataMiningOperation,
							MemoryType memory, const QString& variable, Brain* brain, QObject* parent

	signals:

	public slots:

	};

}
#endif // DELETENOTE_H
