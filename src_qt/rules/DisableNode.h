#ifndef DISABLENODE_H
#define DISABLENODE_H

#include <QtCore/QString>

#include "RuleNode.h"

namespace CnotiMind
{
	class DisableNode : public RuleNode
	{
	public:
		DisableNode( const QString& task, const QString& value, Brain* brain, QObject* parent );

		void exec();
		void exec( QHash<QString, QString>& variables );

		QString info( int depth = 0 ) const;
	private:
		QString _nodeName;
		bool    _toDisable;
	};
}	// CnotiMind

#endif // DISABLENODE_H
