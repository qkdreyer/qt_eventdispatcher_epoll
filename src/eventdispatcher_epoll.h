#ifndef EVENTDISPATCHER_EPOLL_H
#define EVENTDISPATCHER_EPOLL_H

#include <QtCore/QAbstractEventDispatcher>

class EventDispatcherEPollPrivate;
class EventDispatcherLibEventConfig;

class EventDispatcherEPoll : public QAbstractEventDispatcher {
	Q_OBJECT
public:
	explicit EventDispatcherEPoll(QObject* parent = 0);
	virtual ~EventDispatcherEPoll(void);

	virtual bool processEvents(QEventLoop::ProcessEventsFlags flags);
#if QT_VERSION < 0x060000
	virtual bool hasPendingEvents(void);
#endif

	virtual void registerSocketNotifier(QSocketNotifier* notifier);
	virtual void unregisterSocketNotifier(QSocketNotifier* notifier);

	virtual void registerTimer(
		int timerId,
#if QT_VERSION >= 0x060000
		qint64 interval,
#else
		int interval,
#endif
#if QT_VERSION >= 0x050000
		Qt::TimerType timerType,
#endif
		QObject* object
	);

	virtual bool unregisterTimer(int timerId);
	virtual bool unregisterTimers(QObject* object);
	virtual QList<QAbstractEventDispatcher::TimerInfo> registeredTimers(QObject* object) const;
#if QT_VERSION >= 0x050000
	virtual int remainingTime(int timerId);
#endif

	virtual void wakeUp(void);
	virtual void interrupt(void);
#if QT_VERSION < 0x060000
	virtual void flush(void);
#endif

private:
	Q_DISABLE_COPY(EventDispatcherEPoll)
	Q_DECLARE_PRIVATE(EventDispatcherEPoll)
#if QT_VERSION >= 0x040600
	QScopedPointer<EventDispatcherEPollPrivate> d_ptr;
#else
	EventDispatcherEPollPrivate* d_ptr;
#endif
};

#endif // EVENTDISPATCHER_EPOLL_H
