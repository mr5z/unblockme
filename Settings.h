#pragma once

#ifndef _SETTINGS_
#define _SETTINGS_
#endif

const float BLOCK_SIZE = 0.2F;

/*

 __   __   __   __   __   __    __  
|  | |  | |  | |  | |  | |  |  |  | 
|  | |  | |  | |  | |  | |  |  |  | 
|  | |  | |  | |  | |  | |  |  |  | 
|  | |  | |  | |  | |  | |  |  |  | 
|__| |__| |__| |__| |__| |__|  |__| 

*/
const float V_FULL_WIDTH	= BLOCK_SIZE;
const float V_FULL_HEIGHT	= BLOCK_SIZE * 3.f;
const float V_HALF_WIDTH 	= BLOCK_SIZE;
const float V_HALF_HEIGHT 	= BLOCK_SIZE * 2.f;
/*
 ___________   ___________   ___________   ___________
|___________| |___________| |___________| |___________|

 ___________   ___________   ___________   ___________
|___________| |___________| |___________| |___________|

*/
const float H_FULL_WIDTH 	= BLOCK_SIZE * 3.f;
const float H_FULL_HEIGHT 	= BLOCK_SIZE;
const float H_HALF_WIDTH	= BLOCK_SIZE * 2.f;
const float H_HALF_HEIGHT 	= BLOCK_SIZE;