#include "ActionModifiersXmlHandler.h".h"
#include "ActionModifier.h"
#include "Emotion.h"

namespace CnotiMind
{

ActionModifiersXmlHandler::ActionModifiersXmlHandler():
	QXmlDefaultHandler(),
	_emotion(NULL),
	_isCurrentEmotionUsed(false)
{
}

bool ActionModifiersXmlHandler::startElement(const QString &namespaceURI,
											 const QString &localName,
											 const QString &qName,
											 const QXmlAttributes &atts)
{
	Q_UNUSED(namespaceURI);
	Q_UNUSED(localName);

	if( QString::compare( qName, "ActionModifiers", Qt::CaseInsensitive ) == 0 )
	{
		return true;
	}
	if( QString::compare( qName, "Action", Qt::CaseInsensitive ) == 0 )
	{
		return elementAction( atts );
	}
	if( QString::compare( qName, "Emotion", Qt::CaseInsensitive ) == 0 )
	{
		return elementEmotion( atts );
	}
	if( QString::compare( qName, "Property", Qt::CaseInsensitive ) == 0 )
	{
		return elementProperty( atts );
	}
	if( QString::compare( qName, "Order", Qt::CaseInsensitive ) == 0 )
	{
		return elementOrder( atts );
	}
	if( QString::compare( qName, "Modifiers", Qt::CaseInsensitive ) == 0 )
	{
		return elementModifier( atts );
	}

	return false;
}

bool ActionModifiersXmlHandler::endElement(const QString &namespaceURI,
											   const QString &localName,
											   const QString &qName)
{
	Q_UNUSED(namespaceURI);
	Q_UNUSED(localName);
	Q_UNUSED(qName);
	return true;
}

/**
  Handles the xml element Action
*/
bool ActionModifiersXmlHandler::elementAction(const QXmlAttributes &atts)
{
	_action = atts.value("name");
	return true;
}

/**
  Handles the xml element Emotion
*/
bool ActionModifiersXmlHandler::elementEmotion(const QXmlAttributes &atts)
{
	// Delete previous emotion
//	if (_emotion != NULL)
//	{
//		delete _emotion;
//	}

	QString name = atts.value("name");
	// Get max and min values from xml and check if they are numbers
	bool ok;
	qreal max = atts.value("max").toFloat(&ok);
	if (!ok)
	{
		return false;
	}
	qreal min = atts.value("min").toFloat(&ok);
	if (!ok)
	{
		return false;
	}

	if (_emotion == NULL || min != _emotion->min() || max != _emotion->max() ||
			QString::compare(name, _emotion->key(), Qt::CaseInsensitive) == 0)
	{
		if (!_isCurrentEmotionUsed && _emotion != NULL)
		{
			delete _emotion;
		}
		// save current emotion
		_emotion = new Emotion(name, 0, max, min);
	}

	// Reset properties
	_properties.clear();

	return true;
}

/**
  Handles the xml element Property
*/
bool ActionModifiersXmlHandler::elementProperty(const QXmlAttributes &atts)
{
	QString key = atts.value("name");
	QString value = atts.value("value");
	_properties.insert(key, value);
	return true;
}

/**
  Handles the xml element Order
*/
bool ActionModifiersXmlHandler::elementOrder(const QXmlAttributes &atts)
{
	QString order = atts.value("value");
	if( QString::compare( order, "Begin And End", Qt::CaseInsensitive ) == 0 )
	{
		_order = ActionModifier::ExecuteBeforeOrAfter;
	}
	else if( QString::compare( order, "Begin", Qt::CaseInsensitive ) == 0 )
	{
		_order = ActionModifier::ExecuteBefore;
	}
	else if( QString::compare( order, "End", Qt::CaseInsensitive ) == 0 )
	{
		_order = ActionModifier::ExecuteAfter;
	}
	else
	{
		_order = ActionModifier::ExecuteUndefined;
	}

	return true;
}

/**
  Handles the xml element Reinforce Statement
*/
bool ActionModifiersXmlHandler::elementModifier(const QXmlAttributes &atts)
{
	QString name = atts.value("name");
	if (name.isEmpty())
	{
		return false;
	}

	if (!_action.isEmpty() && _emotion != NULL &&
			_order != ActionModifier::ExecuteUndefined)
	{
		ActionModifier* r = new ActionModifier(name, _action, _order,
													   _emotion, _properties);
		_reinforceStatements.append(r);

		_isCurrentEmotionUsed = true;
	}
	return true;
}



QList<ActionModifier *> ActionModifiersXmlHandler::reinforceStatements()
{
	return _reinforceStatements;
}

} // namespace CnotiMind
