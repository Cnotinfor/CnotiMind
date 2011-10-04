#if !defined(_STORAGECOPYNODE_H)
#define _STORAGECOPYNODE_H

#include <QtCore/QString>

#include "RuleNode.h"
#include "../Brain.h"

namespace CnotiMind
{
	class StorageNode : public RuleNode
	{
		Q_OBJECT

	public:
		StorageNode( const QString& event, const QString& value, MemoryType memory, Brain* brain, QObject* parent );

		void exec();
		void exec( QHash<QString, QString>& variables );

		QString info( int depth = 0 ) const;

		static StorageNode *fromXML( const QString &qName, const QXmlAttributes &atts, Brain* brain, QObject* parent );

	protected:
		MemoryType _memory;
		QString    _event;
		QString    _value;
		bool       _clearStorage;
	};

}
#endif  //_STORAGECOPYNODE_H
