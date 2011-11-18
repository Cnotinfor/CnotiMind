#ifndef ACTIONMODIFIER_H
#define ACTIONMODIFIER_H

// Qt
#include <QHash>
#include <QString>

namespace CnotiMind
{
	class Emotion;

	class ActionModifier
	{
	public:
		enum ExecuteOrder {
			ExecuteBefore,
			ExecuteAfter,
			ExecuteBeforeOrAfter,
			ExecuteUndefined
		};

		ActionModifier(const QString& name, const QString& action, int order,
					   Emotion* emotion, QHash<QString, QString> properties);

		QString identification();
		QString action();
		int order();
		Emotion* emotion();
		QHash<QString, QString> properties();
	private:
		QString  _name;		// Modifier identification
		QString  _action;	// Action which this modifier is associated
		int      _order;	// It's done before or after
		Emotion* _emotion;	// Emotion which this modifier is associated
		QHash<QString, QString> _properties;
	};
}

#endif // ACTIONMODIFIER_H
