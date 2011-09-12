#if !defined(_EMOTIONNODE_H)
#define _EMOTIONNODE_H

#include <QtCore/QString>

#include "RuleNode.h"

namespace CnotiMind
{
	class Brain;

	class EmotionNode : public RuleNode
	{
		Q_OBJECT

	public:
		EmotionNode(const QString& key, const QString& value, Brain* brain, QObject* parent);
		EmotionNode(const QString& key, const QString& value, qreal max, qreal min, Brain* brain, QObject* parent);

		void exec();
		void exec( QHash<QString, QString>& variables );

		QString info( int depth = 0 ) const;

		static EmotionNode *fromXML( const QString &qName, const QXmlAttributes &atts, Brain* brain, QObject* parent );

	protected:
		QString _emotion;
		QString _value;
		qreal _min;
		qreal _max;
		qreal _valueNumeric;
		bool _valueNumericOk;
	};

}
#endif  //_EMOTIONNODE_H
