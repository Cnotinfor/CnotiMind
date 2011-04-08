#if !defined(_PERCEPTION_H)
#define _PERCEPTION_H

#include <QtCore/QString>
#include <QtCore/QVariant>

#include "CnotiMind_global.h"
#include "Node.h"

namespace CnotiMind
{

	class CNOTIMIND_EXPORT Perception
	{
	public:
		Perception( const QString& name, const QVariant& value );

		const QString& name() const;
		const QVariant& value() const;

	protected:
		QString _name;
		QVariant _value;
	};

}
#endif  //_PERCEPTION_H
