#if !defined(_ACTIONNODE_H)
#define _ACTIONNODE_H

#include <QtCore/QString>
#include "RuleNode.h"

namespace CnotiMind
{
	class Brain;

	class ActionNode : public RuleNode
	{
		Q_OBJECT

	public:
		ActionNode( const QString& key, const QString& value, const QString probability, Brain* brain, QObject* parent );

		void exec();
		void exec( QHash<QString, QString>& variables );

		QString info( int depth ) const;

	protected:
		QString _name;
		QString _value;
		QString _probability;
		qreal   _probabilityValue; // Between 0 and 1
		bool    _isProbabilityNumeric;

	};

}

#endif  //_ACTIONNODE_H
