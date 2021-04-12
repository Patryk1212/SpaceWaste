#pragma once

#include "events+input/Message.h"

/* messages types */
//class MainLayerMessage : public Engine::Message
//{
//public:
//	MainLayerMessage() = default;
//	virtual ~MainLayerMessage() = default;
//
//	int speed = 0;
//	bool start = true;
//	int objectNumber = 0;
//};
//
//class UILayerMessage : public Engine::Message
//{
//public:
//	UILayerMessage() = default;
//	UILayerMessage(int totalNumberOfObjects_) : totalNumberOfObjects(totalNumberOfObjects_) {}
//	virtual ~UILayerMessage() = default;
//
//	int totalNumberOfObjects = 0;
//	void* objects;
//};

///* base */
//class Observer
//{
//public:
//	virtual ~Observer() = default;
//
//	virtual void onUpdate1(const Message& message) = 0;
//};
//
//class Subject
//{
//public:
//	virtual ~Subject() {}
//	virtual void Attach(Observer* observer) = 0;
//	virtual void Detach(Observer* observer) = 0;
//	virtual void Notify() = 0;
//};
//
///* subjects to be held in layer classes */
//class DataForMainLayer : public Subject
//{
//public:
//	DataForMainLayer() = default;
//	~DataForMainLayer() = default;
//
//	void onUpdateData(int speed_, bool start_, int objectNumber_) 
//	{
//		message.speed = speed_; message.start = start_; message.objectNumber = objectNumber_; Notify();
//	}
//
//	virtual void Attach(Observer* observer) override { mainLayer = observer; }
//	virtual void Detach(Observer* observer) override { mainLayer = nullptr; }
//	virtual void Notify() override 
//	{
//		mainLayer->onUpdate1(message); 
//	}
//
//private:
//	Observer* mainLayer;
//
//private:
//	MainLayerMessage message;
//};
//
//class DataForUILayer : public Subject
//{
//public:
//	DataForUILayer() = default;
//	~DataForUILayer() = default;
//
//	void onUpdateData(int numberOfObjects_, std::vector<std::unique_ptr<SpaceObject>> objects_)
//	{
//		message.totalNumberOfObjects = numberOfObjects_;  Notify();
//	}
//
//	virtual void Attach(Observer* observer) override { uiLayer = observer; }
//	virtual void Detach(Observer* observer) override { uiLayer = nullptr; }
//	virtual void Notify() override { uiLayer->onUpdate1(message); }
//
//private:
//	Observer* uiLayer;
//
//private:
//	UILayerMessage message;
//};
