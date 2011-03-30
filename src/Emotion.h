#if !defined(_EMOTION_H)
#define _EMOTION_H

#include <QtCore/QString>

namespace CnotiMind
{

	class Emotion
	{
	public:
		Emotion(const QString& key, int value);
		Emotion(const QString& key, int value, int max, int min);

		int value() const;
		const QString& key() const;

	protected:
		int _value;
		int _max;
		int _min;
		QString _key;
	};

}
#endif  //_EMOTION_H
