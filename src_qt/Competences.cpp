#include <QtCore/QString>
#include "Competences.h"

namespace CnotiMind
{

	Competences::Competences( QObject* parent ):
		QObject( parent )
	{

	}

	Competences::Competences( const QString& path, QObject* parent ):
		QObject( parent )
	{

	}

	Competences::Competences( const QString& path, const Brain* brain, QObject* parent ):
		QObject( parent )
	{

	}

	bool Competences::loadXML( const QString& path )
	{
		return true;
	}

	void Competences::newAction( const Action& action )
	{

	}

	void Competences::changeEmotion( const QString& emotion, qreal newValue )
	{

	}

	void Competences::connectToBrain( const Brain* brain )
	{

	}

}
