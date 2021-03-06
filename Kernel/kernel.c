#include "heap.h"
#include "interrupts.h"
#include "lib.h"
#include "memoryManager.h"
#include "moduleLoader.h"
#include "scheduler.h"
#include "systemcalls.h"
#include "video_driver.h"
#include "mutex.h"

extern byte bss;
extern byte endOfKernelBinary;
extern byte endOfKernel;

static const qword PageSize = 0x1000;

void * kernelStack;

static void * shell = (void *) 0x600000;
static void * linearGraph = (void *) 0x800000;
static void * parabolicGraph = (void *) 0x900000;
static void * processRead = (void *) 0xA00000;
static void * testMemoryManager = (void *) 0xB00000;
static void * processWrite = (void *) 0xC00000;
static void * background = (void *) 0xD00000;
static void * processReadAndWrite = (void *) 0xE00000;
static void * processWriteAndRead = (void *) 0xF00000;
static void * producer = (void *) 0xF10000;
static void * consumer = (void *) 0xF20000;

void clearBSS(void * bssAddress, qword bssSize){
	memset(bssAddress, 0, bssSize);
}

void * getStackBase(){
	return (void *)(
		(qword)&endOfKernel
		+ PageSize * 8		  	/* The size of the stack itself, 32KiB */
		- sizeof(qword)			/* Begin at the top of the stack */
	);
}

void * initializeKernelBinary(){
	void * moduleAddresses[] = {shell, linearGraph, parabolicGraph, processRead, 
		testMemoryManager, processWrite, background,processReadAndWrite,processWriteAndRead, producer, consumer,};
	loadModules(&endOfKernelBinary, moduleAddresses);
	clearBSS(&bss, &endOfKernel - &bss);
	return getStackBase();
}

void initializeKernelStack(){
	kernelStack = (void *) allocPage(PAGE_SIZE * 2);
}

void initializeKernelMemory(){
	allocPage(20 * PAGE_SIZE);
}

void reserveMemoryForMemoryManager(){
	allocPage(sizeof(memoryManager));
}

int main(){
	_cli();		
	load_idt();
	load_systemcalls();
	start_video_mode();
	_sti();

	initializeMemoryManager();
	initializeKernelMemory();
	initializeKernelStack();
	reserveMemoryForMemoryManager();
	initializeKernelHeap();
	initiliazeMutexes();
	startProcess(shell, "shell");
	return 0;
}
