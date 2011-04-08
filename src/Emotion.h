#if !defined(_EMOTION_H)
#define _EMOTION_H

#include <QtCore/QString>
#include <QtCore/QDataStream>
#include <QtCore/QStringList>

#include "CnotiMind_global.h"

namespace CnotiMind
{

	class CNOTIMIND_EXPORT Emotion
	{
	public:
		Emotion();
		Emotion(const QString& key, qreal value);
		Emotion(const QString& key, qreal value, qreal max, qreal min);

		qreal value() const;
		const QString& key() const;
		bool setValue( qreal newValue, qreal max, qreal min );
		bool setValue( qreal newValue );
		bool addValue( qreal increment, qreal max, qreal min );
		bool addValue( qreal increment );

		friend bool operator==(const Emotion& emotion, const QString& emotionName);
		friend bool operator==(const QString& emotionName, const Emotion& emotion);
		friend bool operator==(const Emotion& e1, const Emotion& e2);
		friend bool operator==(const Emotion& e1, const Emotion& e2);
		friend QDataStream& operator<< ( QDataStream & out, const Emotion& e);
		friend QStringList&	operator<< ( QStringList& list, const Emotion& e );

	protected:
		qreal _value;
		qreal _max;
		qreal _min;
		QString _key;
	};

}
#endif  //_EMOTION_H
