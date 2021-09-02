#pragma once
class Cproduct
{
private:

public:
	Cproduct() = default;
	virtual ~Cproduct() = default;

	virtual void doStuff() abstract;

	void someOperation(){}
};