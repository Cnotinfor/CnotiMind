#if !defined(_PERCEPTION_H)
#define _PERCEPTION_H

#include <QtCore/QString>
#include "Node.h"

namespace CnotiMind
{

	class Perception : public Node
	{
	public:
		Perception( const QString& key, const QString& value );
	};

}
#endif  //_PERCEPTION_H
