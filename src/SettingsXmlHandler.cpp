#include <QtCore/QDebug>

#include "SettingsXmlHandler.h"
#include "Brain.h"
#include "Emotion.h"

namespace CnotiMind
{

	SettingsXmlHandler::SettingsXmlHandler( Brain* brain):
		_brain( brain ),
		_insidePerception( false ),
		_insideAction( false ),
		_insideEmotion( false ),
		_insideValue( false ),
		_needValues( false ),
		_elementType( "" ),
		TYPE( "type" ),
		TYPE_INT( "int" ),
		TYPE_STRING( "string" ),
		TYPE_VALUES( "values" ),
		NAME( "name" )
	{
	}

	bool SettingsXmlHandler::startElement ( const QString & namespaceURI, const QString & localName, const QString & qName, const QXmlAttributes & atts )
	{

		if( QString::compare( qName, "Settings", Qt::CaseInsensitive ) == 0 )
		{
			return true;
		}
		if( QString::compare( qName, "Perception", Qt::CaseInsensitive ) == 0 )
		{
			return elementPerception( atts );
		}
		if( QString::compare( qName, "Action", Qt::CaseInsensitive ) == 0 )
		{
			return elementAction( atts );
		}
		if( QString::compare( qName, "Emotion", Qt::CaseInsensitive ) == 0 )
		{
			return elementEmotion( atts );
		}
		if( QString::compare( qName, "Value", Qt::CaseInsensitive ) == 0 )
		{
			// Test if it an element values appears, but it not child
			// from Emotion, Action or Perception element
			if( !_insidePerception && !_insideAction && !_insideEmotion )
			{
				return false;
			}
			// Test if it is already inside a Value element, it shouldn't have another child Value element
			if( _insideValue )
			{
				return false;
			}
			_insideValue = true;
			return true;
		}

		return false;
	}

	bool SettingsXmlHandler::endElement( const QString & namespaceURI, const QString & localName, const QString & qName )
	{
		if( QString::compare( qName, "Settings", Qt::CaseInsensitive ) == 0 )
		{
			return true;
		}
		if( QString::compare( qName, "Perception", Qt::CaseInsensitive ) == 0 )
		{
			return endElementPerception();
		}
		if( QString::compare( qName, "Action", Qt::CaseInsensitive ) == 0 )
		{
			return endElementAction();
		}
		if( QString::compare( qName, "Emotion", Qt::CaseInsensitive ) == 0 )
		{
			return endElementEmotion();
		}
		if( QString::compare( qName, "Value", Qt::CaseInsensitive ) == 0 )
		{
			_insideValue = false;
			return true;
		}
		return false;
	}

	/**
		TODO

		Not sure if it should have support for possible values for the elements
	*/
	bool SettingsXmlHandler::characters( const QString & ch )
	{
		if( _insideValue && (_insidePerception || _insideAction || _insideEmotion) )
		{
			//_possibleValues.append( ch );
		}
		return true;
	}

	bool SettingsXmlHandler::elementPerception( const QXmlAttributes & atts )
	{
		// Test if it inside another element
		if( _insidePerception || _insideAction || _insideEmotion )
		{
			return false;
		}

		// Check it it need values for the perception
		_needValues = QString::compare( atts.value( TYPE ), TYPE_VALUES, Qt::CaseInsensitive ) == 0;
		_possibleValues.clear();

		// Get the perception name
		_elementName = atts.value( NAME );
		if(_elementName.isEmpty())
		{
			return false;
		}

		_insidePerception = true;

		return true;
	}

	bool SettingsXmlHandler::elementAction( const QXmlAttributes & atts )
	{
		// Test if it inside another element
		if( _insidePerception || _insideAction || _insideEmotion )
		{
			return false;
		}

		// Get the action name
		_elementName = atts.value( NAME );
		if(_elementName.isEmpty())
		{
			return false;
		}

		_insideAction = true;
		return true;
	}

	bool SettingsXmlHandler::elementEmotion( const QXmlAttributes & atts )
	{
		// Test if it inside another element
		if( _insidePerception || _insideAction || _insideEmotion )
		{
			return false;
		}

		// Get the emotion name
		_elementName = atts.value( NAME );
		if(_elementName.isEmpty())
		{
			return false;
		}

		// Test if it has all the attributes required for the emotions
		if( atts.index( "value" ) != -1 &&
			atts.index( "max" ) != -1 &&
			atts.index( "min" ) != -1 )
		{
			bool ok;
			int i;
			_emotionAttributes.clear();
			i = atts.value( "value" ).toInt( &ok );
			if(!ok)
			{
				qWarning() << "[SettingsXmlHandler::elementEmotion] Invalid attribute value: value =" << i;
				return false;
			}
			_emotionAttributes.append( i );

			i = atts.value( "max" ).toInt( &ok );
			if(!ok)
			{
				qWarning() << "[SettingsXmlHandler::elementEmotion] Invalid attribute value: max =" << i;
				return false;
			}
			_emotionAttributes.append( i );

			i = atts.value( "min" ).toInt( &ok );
			if(!ok)
			{
				qWarning() << "[SettingsXmlHandler::elementEmotion] Invalid attribute value: min =" << i;
				return false;
			}
			_emotionAttributes.append( i );
		}
		else
		{
			return false;
		}

		_insideEmotion = true;
		return true;
	}

	bool SettingsXmlHandler::endElementPerception()
	{
		if( _insidePerception )
		{
			_brain->addValidPerception( _elementName );
			_insidePerception = false;
			return true;
		}
		return false;
	}

	bool SettingsXmlHandler::endElementAction()
	{
		if( _insideAction )
		{
			_brain->addValidAction( _elementName );
			_insideAction = false;
			return true;
		}
		return false;
	}

	bool SettingsXmlHandler::endElementEmotion()
	{
		if( _insideEmotion )
		{
			Emotion e( _elementName, _emotionAttributes.at( 0 ), _emotionAttributes.at( 1 ), _emotionAttributes.at( 2 ) );
			_brain->addEmotion( e );
			_insideEmotion = false;
			return true;
		}
	}


} // end namespace
