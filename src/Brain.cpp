#include <QtCore/QString>
#include <QtCore/QDebug>

#include "Brain.h"
#include "SettingsXmlHandler.h"
#include "rules/RuleNode.h"

namespace CnotiMind
{

	Brain::Brain( const QString& path, QObject* parent ):
		QThread( parent )
	{
		loadXmlSettings( path );

	}

	Brain::Brain( QObject* parent ):
		QThread( parent )
	{

	}

	/**
		Load a XML file with settings.

		This method can me called several times, append new settings to the Brain.

		XML file can have Perceptions, Actions and Emotions
	*/
	bool Brain::loadXmlSettings( const QString& filename )
	{
		QFile f( filename );

		SettingsXmlHandler *handler = new SettingsXmlHandler( this );
		QXmlInputSource source( &f );
		if( source.data() == "" )
		{
			qWarning() << "[Brain::loadXmlSettings] File not found" << filename;
			return false;
		}

		QXmlSimpleReader reader;
		reader.setContentHandler( handler );

		// Retrives data from file
		return reader.parse( source );
	}

	/**
		Add a perception to the brain.

		Only perceptions
	*/
	void Brain::addValidPerception( const QString& perception )
	{
		_validPerceptions.append( perception );
	}

	/**
		Add an action to the brain.

		If no actions are added to the brain, it will not be possible for the brain
		to send actions to be executed. Only action added to the brain are sent.
	*/
	void Brain::addValidAction( const QString& action )
	{
		_validActions.append( action );
	}

	/**
		Emotions the brain reacts to.

		If no emotions are added to the brain, it will not react to emotion changes
		defined on the rules.
	*/
	void Brain::addEmotion( const Emotion& emotion )
	{
		_emotions.append( emotion );
	}

	bool Brain::loadXmlRules( const QString& filename )
	{
		return true;
	}

	bool Brain::validateXML(int xml)
	{
		return true;
	}

	bool Brain::saveMemory(const QString& filename)
	{
		return true;
	}

	bool Brain::loadMemory(const QString& filename)
	{
		return true;
	}

	bool Brain::saveEmotionalState(const QString& filename)
	{
		return true;
	}

	bool Brain::loadEmotionalState(const QString& filename)
	{
		return true;
	}

	/**
		Main loop for the thread.

		Everytime a perceptions arrives, this thread
	*/
	void Brain::run()
	{
		while( true )
		{
			// wait for perceptions being available
			_semaphorePerceptions.acquire();

			_rules->exec();
		}
	}

	void Brain::clearWorkingMemory()
	{

	}

	void Brain::clearMemory()
	{

	}

	void Brain::sendAction(const Action& action)
	{

	}

	void Brain::sendEmotionalState(const QString& state, int value)
	{

	}

	void Brain::receivePerception( const Perception& perception )
	{
		_receivedPerceptions.append( perception );

		// changing the semaphore, so that
		_semaphorePerceptions.release();
	}


	bool Brain::createRules(int xml)
	{
		return true;
	}

	RuleNode* Brain::createNode(int xml, RuleNode* parent)
	{
		return NULL;
	}

	ActionNode* Brain::createActionNode(int xml, RuleNode* parent)
	{
		return NULL;
	}

	StorageNode* Brain::createStorageNode(int xml, RuleNode* parent)
	{
		return NULL;
	}

	EmotionNode* Brain::createEmotionNode(int xml, RuleNode* parent)
	{
		return NULL;
	}

	ConditionNode* Brain::createConditionNode(int xml, RuleNode* parent)
	{
		return NULL;
	}

	ConditionEventNode* Brain::createConditionEventNode(int xml, RuleNode* parent)
	{
		return NULL;
	}

	ConditionEmotionNode* Brain::createConditionEmotionNode(int xml, RuleNode* parent)
	{
		return NULL;
	}

	ConditionDataMiningNode* Brain::createConditionDataMiningNode(int xml, RuleNode* parent)
	{
		return NULL;
	}

	void Brain::updateEmotionalState(const QString& state, int variation, int max, int min)
	{

	}

	void Brain::updateEmotionalState(const QString& state, int variation)
	{

	}

}
