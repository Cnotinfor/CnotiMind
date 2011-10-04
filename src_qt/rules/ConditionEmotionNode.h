#if !defined(_CONDITIONEMOTIONNODE_H)
#define _CONDITIONEMOTIONNODE_H

#include <QtCore/QString>

#include "ConditionNode.h"
#include "../Emotion.h"

namespace CnotiMind
{
	class Brain;

	class ConditionEmotionNode : public ConditionNode
	{
		Q_OBJECT

	public:
		ConditionEmotionNode( const QString& emotion, const QString& value, ConditionOperator op, Brain* brain, QObject* parent );

		void exec();
		void exec( QHash<QString,QString>& variables );

		QString info( int depth = 0 ) const;

		static ConditionEmotionNode *fromXML( const QString &qName, const QXmlAttributes &atts, Brain* brain, QObject* parent );

	protected:
		bool isTrue();
		bool testEmotion( const Emotion& e ) const;

		QString _emotion;
		QString _value;
		qreal _valueNumeric;
		bool _isValueNumeric;
	};

}
#endif  //_CONDITIONEMOTIONNODE_H
