#if !defined(_CONDITIONPERCEPTIONNODE_H)
#define _CONDITIONPERCEPTIONNODE_H

#include <QtCore/QString>

#include "ConditionNode.h"

namespace CnotiMind
{
	class Brain;

	class ConditionPerceptionNode : public ConditionNode
	{
		Q_OBJECT

	public:
		ConditionPerceptionNode(const QString& perception, const QString& value, ConditionOperator op, Brain* brain, QObject* parent);

		void exec();
		void exec( QHash<QString,QString>& variables );

		QString info( int depth = 0 ) const;

		static ConditionPerceptionNode *fromXML( const QString &qName, const QXmlAttributes &atts, Brain* brain, QObject* parent );

	protected:
		bool isTrue();

		QString _perception;
		QString _value;
		qreal _valueNumeric;
		bool _isValueNumeric;

	};

}
#endif  //_CONDITIONPERCEPTIONNODE_H
