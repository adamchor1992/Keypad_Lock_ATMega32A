#include "keypad_lock.h"

int main(void)
{
	KeypadLock keypadLock;
	
	while(1)
	{
		keypadLock.Execute();
	}
}