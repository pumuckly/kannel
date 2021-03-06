/* ==================================================================== 
 * The Kannel Software License, Version 1.0 
 * 
 * Copyright (c) 2001-2019 Kannel Group
 * Copyright (c) 1998-2001 WapIT Ltd.   
 * All rights reserved. 
 * 
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions 
 * are met: 
 * 
 * 1. Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer. 
 * 
 * 2. Redistributions in binary form must reproduce the above copyright 
 *    notice, this list of conditions and the following disclaimer in 
 *    the documentation and/or other materials provided with the 
 *    distribution. 
 * 
 * 3. The end-user documentation included with the redistribution, 
 *    if any, must include the following acknowledgment: 
 *       "This product includes software developed by the 
 *        Kannel Group (http://www.kannel.org/)." 
 *    Alternately, this acknowledgment may appear in the software itself, 
 *    if and wherever such third-party acknowledgments normally appear. 
 * 
 * 4. The names "Kannel" and "Kannel Group" must not be used to 
 *    endorse or promote products derived from this software without 
 *    prior written permission. For written permission, please  
 *    contact org@kannel.org. 
 * 
 * 5. Products derived from this software may not be called "Kannel", 
 *    nor may "Kannel" appear in their name, without prior written 
 *    permission of the Kannel Group. 
 * 
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED 
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
 * DISCLAIMED.  IN NO EVENT SHALL THE KANNEL GROUP OR ITS CONTRIBUTORS 
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,  
 * OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT  
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR  
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,  
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE  
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,  
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 * ==================================================================== 
 * 
 * This software consists of voluntary contributions made by many 
 * individuals on behalf of the Kannel Group.  For more information on  
 * the Kannel Group, please see <http://www.kannel.org/>. 
 * 
 * Portions of this software are based upon software originally written at  
 * WapIT Ltd., Helsinki, Finland for the Kannel project.  
 */ 

/*
 * test_msg.c - test message manipulation
 * 
 * This file is a test program for the message manipulation functions in 
 * msg.h and msg.c.
 * 
 * Lars Wirzenius <liw@wapit.com> 
 */


#include "gw/msg.h"
#include "gwlib/gwlib.h"

int main(void) {
	Msg *msg, *msg2;
	Octstr *os;
	
	gwlib_init();

	info(0, "Creating msg.");
	msg = msg_create(heartbeat);
	msg->heartbeat.load = 42;
	msg_dump(msg, 0);
	
	info(0, "Packing msg.");
	os = msg_pack(msg);
	octstr_dump(os, 0);
	
	info(0, "Unpacking msg to msg2.");
	msg2 = msg_unpack(os);
	info(0, "msg2->heartbeat.load: %ld", (long) msg2->heartbeat.load);

	info(0, "Destroying msg and msg2.");
	msg_destroy(msg);
	msg_destroy(msg2);
	
	info(0, "Creating sms.");
	msg = msg_create(sms);
	msg->sms.sender = octstr_create("123");
	msg->sms.receiver = octstr_create("456");
	msg->sms.msgdata = octstr_create("hello, world");
	
	info(0, "Packing sms.");
	os = msg_pack(msg);
	octstr_dump(os, 0);
	
	info(0, "Duplicating msg.");
	msg2 = msg_duplicate(msg);
	msg_dump(msg2, 0);
	msg_destroy(msg2);

	info(0, "Unpacking sms.");
	msg2 = msg_unpack(os);
	info(0, "msg2:");
	info(0, "  sender: %s", octstr_get_cstr(msg->sms.sender));
	info(0, "  receiv: %s", octstr_get_cstr(msg->sms.receiver));
	info(0, "  msgdata  : %s", octstr_get_cstr(msg->sms.msgdata));

	return 0;
}
