#include "ActionModifier.h"

namespace CnotiMind
{
	ActionModifier::ActionModifier(const QString& name, const QString& action,
								   int order, Emotion* emotion,
								   QHash<QString, QString> properties) :
		_name(name),
		_action(action),
		_order(order),
		_emotion(emotion),
		_properties(properties)
	{
	}

	QString ActionModifier::identification()
	{
		return _name;
	}

	QString ActionModifier::action()
	{
		return _action;
	}

	int ActionModifier::order()
	{
		return _order;
	}

	Emotion* ActionModifier::emotion()
	{
		return _emotion;
	}

	QHash<QString, QString> ActionModifier::properties()
	{
		return _properties;
	}
}
