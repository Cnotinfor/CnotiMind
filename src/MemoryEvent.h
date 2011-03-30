#if !defined(_MEMORYEVENT_H)
#define _MEMORYEVENT_H

#include <QtCore/QString>
#include <ctime>

#include "Node.h"

namespace CnotiMind
{

	class MemoryEvent: public Node
	{
	public:
		MemoryEvent( const QString& key, const QString& value );
		MemoryEvent( const QString& key, const QString& value, time_t time );

		time_t time() const;
		const QString& key() const;
		const QString& value() const;

	protected:
		time_t _time;
		QString _key;
		QString _value;
	};

}
#endif  //_MEMORYEVENT_H
