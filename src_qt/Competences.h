#if !defined(_COMPETENCES_H)
#define _COMPETENCES_H

#include <QtCore/QString>
#include <QtCore/QObject>
#include <QtCore/QList>

#include "CnotiMind_global.h"
#include "Brain.h"
#include "Perception.h"

namespace CnotiMind
{
	class CNOTIMIND_EXPORT Competences: public QObject
	{
		Q_OBJECT

	public:
		Competences( QObject* parent );
		Competences( const QString& path, QObject* parent );
		Competences( const QString& path, const Brain* brain, QObject* parent );

		bool loadXML( const QString& path );
		//void newAction( const Action& action );
		void changeEmotion( const QString& emotion, qreal newValue );
		void connectToBrain( const Brain* brain );

	private:
		QList<Perception> _perceptions;
		QList<Emotion> _emotions;
	};

}

#endif  //_COMPETENCES_H
