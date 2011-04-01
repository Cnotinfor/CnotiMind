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
		Emotion(const QString& key, int value);
		Emotion(const QString& key, int value, int max, int min);

		int value() const;
		const QString& key() const;
		bool setValue( int newValue, int max, int min );
		bool setValue( int newValue );
		bool addValue( int increment, int max, int min );
		bool addValue( int increment );

		friend bool operator==(const Emotion& emotion, const QString& emotionName);
		friend bool operator==(const QString& emotionName, const Emotion& emotion);
		friend bool operator==(const Emotion& e1, const Emotion& e2);
		friend bool operator==(const Emotion& e1, const Emotion& e2);
		friend QDataStream& operator<< ( QDataStream & out, const Emotion& e);
		friend QStringList&	operator<< ( QStringList& list, const Emotion& e );

	protected:
		int _value;
		int _max;
		int _min;
		QString _key;
	};

}
#endif  //_EMOTION_H
