#ifndef DELETENODE_H
#define DELETENODE_H

#include "RuleNode.h"
#include "../CnotiMind.h"

namespace CnotiMind
{

	class DeleteNode : public RuleNode
	{
		Q_OBJECT
	public:
		explicit DeleteNode( const QString& key, const QString& value, DeletePosition position,
							 MemoryType memory, Brain* brain, QObject* parent );

		void exec();
		void exec( QHash<QString, QString>& variables );

		QString info( int depth = 0 ) const;

		static DeleteNode *fromXML( const QString &qName, const QXmlAttributes &atts, Brain* brain, QObject* parent );

	private:
		QString _key;
		QString _value;
		DeletePosition _position;
		MemoryType _memory;

	};

}
#endif // DELETENODE_H
