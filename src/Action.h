#if !defined(_ACTION_H)
#define _ACTION_H

#include <QtCore/QString>

#include "CnotiMind_global.h"
#include "Node.h"

namespace CnotiMind
{

	class CNOTIMIND_EXPORT Action : public Node
	{
	public:
		Action( const QString& key, const QString& value );
	};

}

#endif  //_ACTION_H
