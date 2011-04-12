#ifndef OBJECTTOXML_H
#define OBJECTTOXML_H

#include <QString>

namespace CnotiMind
{

	class ObjectToXml
	{
	public:
		ObjectToXml();

		virtual QString toXml() const = 0;
	};

}
#endif // OBJECTTOXML_H
