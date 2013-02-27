/*
 * ProgramLoop.h
 *
 *  Created on: Feb 26, 2013
 *      Author: bracz
 */

#ifndef PROGRAMLOOP_H_
#define PROGRAMLOOP_H_

#ifndef __cplusplus
// Trampoline from C main file to C++ main class.
void RunProgramLoop();
#else
class ProgramLoop {
public:
	ProgramLoop();
	void Init();
	void Run();
	virtual ~ProgramLoop();
};
#endif // cplusplus
#endif /* PROGRAMLOOP_H_ */
