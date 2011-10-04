#ifndef DATAMININGNODE_H
#define DATAMININGNODE_H

#include <QtCore/QVariant>

#include "RuleNode.h"
#include "../CnotiMind.h"

namespace CnotiMind
{
	class Brain;

	class DataMiningNode : public RuleNode
	{
		Q_OBJECT

	public:
		DataMiningNode(const QString& key, const QString& value, DataMiningOperation operation,
					   MemoryType memory, const QString& variable, const QString& position, Brain* brain, QObject* parent);

		void exec();
		void exec( QHash<QString, QString>& variables );

		QString info( int depth = 0 ) const;

		static DataMiningNode *fromXML( const QString &qName, const QXmlAttributes &atts, Brain* brain, QObject* parent );

	protected:
		bool isTrue( const QHash<QString, QString>& variables );

		QString _event;
		QString _value;
		const DataMiningOperation _operation;
		const MemoryType _memory;
		const QString _variable;
		qreal _valueNumeric;
		bool _isValueNumeric;
		QVariant _result;
		QString _position;
		bool _isPositionNumeric;
		int _positionNumeric;

	};

}

#endif // DATAMININGNODE_H
