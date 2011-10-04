#ifndef CLEARMEMORYNODE_H
#define CLEARMEMORYNODE_H

#include "RuleNode.h"
#include "../CnotiMind.h"

namespace CnotiMind
{
	/**
	 *
	 * Clears all events in the memory specified.
	 *
	 */
	class ClearMemoryNode : public RuleNode
	{
		Q_OBJECT
	public:
		explicit ClearMemoryNode( const MemoryType& memory, Brain* brain, QObject* parent );

		void exec();
		void exec( QHash<QString, QString>& variables );

		QString info( int depth = 0 ) const;

		static ClearMemoryNode *fromXML( const QString &qName, const QXmlAttributes &atts, Brain* brain, QObject* parent );

	private:
		MemoryType _memory;
	};

}
#endif // CLEARMEMORYNODE_H
