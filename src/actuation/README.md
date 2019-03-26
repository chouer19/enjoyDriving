test method

step 1.
        print to terminal
	test if this could read deke steering system feedback CAN

step 2.
        another sub tool subcribe feedback msg
	test if pub can publish the msg

step 3.
	assign write_frame constant steering arguments
	test if this could wirte control CAN to deke steering system

step 4.
	another pub tool publish control msg
	test if sub can subciribe it and print to terminal

step 5.
	another pub tool publish control msg
	test if the steering wheel rotate as predefined
