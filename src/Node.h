#if !defined(_NODE_H)
#define _NODE_H

#include <QtCore/QString>

namespace CnotiMind
{

	class Node
	{
	public:
		Node(const QString& key, const QString& value);

		const QString& value() const;
		const QString& key() const;

	protected:
		QString _key;
		QString _value;
	};

}
#endif  //_NODE_H
