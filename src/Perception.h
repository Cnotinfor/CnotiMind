#if !defined(_PERCEPTION_H)
#define _PERCEPTION_H

#include <QtCore/QString>

#include "CnotiMind_global.h"
#include "Node.h"

namespace CnotiMind
{

	class CNOTIMIND_EXPORT Perception : public Node
	{
	public:
		Perception( const QString& key, const QString& value );
	};

}
#endif  //_PERCEPTION_H
