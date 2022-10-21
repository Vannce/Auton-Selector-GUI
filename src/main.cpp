#include "main.h"
#include "pros/apix.h"


void Checkers(lv_obj_t* Square, lv_color32_t color, int x, int y);
void Roller(lv_obj_t* roller,int w, int h, int x, int y);
void BlueZones(lv_obj_t* zone, int w, int h, int x, int y);
void Button(lv_obj_t* button, lv_obj_t* Page, int w, int h, int posx, int posy, lv_color32_t color/*Name, Page, Size, Position, Color, */);

int AutonomousMode = 0; //solo(1) or team(2)
int AutonStart = 0; //4 places
bool PageShown = false;
bool LabelShown = !PageShown;
int AutonSelectPage = 255; //hidden(0) or shown (255)

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

/*---------------GUI------------------*/
//Next Page
lv_obj_t * BackButton;
lv_obj_t * BackButtonLabel;
lv_obj_t * myLabel;

lv_style_t LabelStyle;
lv_style_t BackButtonPressed;
lv_style_t BackButtonReleased;




/*---------------Pages-----------------*/
lv_obj_t * AutonField = lv_page_create(lv_scr_act(), NULL);
lv_style_t FieldStyle;

lv_obj_t * AutonSelect = lv_page_create(lv_scr_act(), NULL);
lv_style_t SelectStyle;



/*------------Buttons-------------*/
//Blue1
lv_obj_t * BlueButton= lv_btn_create(AutonField, NULL);
lv_style_t BlueButtonReleased; //relesed style
lv_style_t BlueButtonPressed; //pressed style
//Red1
lv_obj_t * RedButton= lv_btn_create(AutonField, NULL);
lv_style_t RedButtonReleased; //relesed style
lv_style_t RedButtonPressed; //pressed style
//Blue2
lv_obj_t * BlueButton2= lv_btn_create(AutonField, NULL);
lv_style_t BlueButton2Released; //relesed style
lv_style_t BlueButton2Pressed; //pressed style
//Red2
lv_obj_t * RedButton2= lv_btn_create(AutonField, NULL);
lv_style_t RedButton2Released; //relesed style
lv_style_t RedButton2Pressed; //pressed style

//Auton Select

lv_obj_t * TeamButton = lv_btn_create(AutonSelect, NULL);
lv_obj_t * SoloButton = lv_btn_create(AutonSelect, NULL);
lv_obj_t * TeamLabel;
lv_obj_t * SoloLabel;
lv_style_t ButtonPressed;
lv_style_t ButtonReleased;



/*--------Field----------*/

//Checker Patern
lv_obj_t * object;
lv_obj_t * object1;
lv_obj_t * object2;
lv_obj_t * object3;
lv_obj_t * object4;
lv_obj_t * object5;
lv_obj_t * object6;
lv_obj_t * object7;
lv_obj_t * object8;
lv_obj_t * object9;
lv_obj_t * object10;
lv_obj_t * object11;
lv_obj_t * object12;
lv_style_t checkers;

//Rollers
lv_obj_t * roller1;
lv_obj_t * roller2;
lv_obj_t * roller3;
lv_obj_t * roller4;
lv_style_t rollers;

//Alliance Zones
lv_obj_t * BlueZone1;
lv_obj_t * BlueZone2;
lv_obj_t * RedZone1;
lv_obj_t * RedZone2;
lv_style_t BlueAllianceZones;
lv_style_t RedAllianceZones;





void Checkers(lv_obj_t* square, lv_color32_t color, int x, int y){
	square = lv_obj_create(AutonField,NULL);
	lv_obj_set_size(square, 80, 40);
	lv_obj_align(square, NULL, LV_ALIGN_IN_TOP_LEFT, x, y);//position
		lv_style_copy(&checkers, &lv_style_plain);
		checkers.body.main_color = color;// color (grey or black)
		checkers.body.grad_color = color;// color (grey or black)
		checkers.body.radius = 0;
		checkers.body.border.width = 0;
		checkers.text.color = LV_COLOR_MAKE(255, 255, 255);
	lv_obj_set_style(square, &checkers);
}

void BlueZones(lv_obj_t* zone, int w, int h, int x, int y){
	zone = lv_obj_create(AutonField, NULL);
	lv_obj_set_size(zone, w, h);//size
	lv_obj_align(zone, NULL, LV_ALIGN_IN_TOP_LEFT, x, y);//position
	lv_style_copy(&BlueAllianceZones, &lv_style_plain);
		BlueAllianceZones.body.main_color = LV_COLOR_BLUE;
		BlueAllianceZones.body.grad_color = LV_COLOR_BLUE;
		BlueAllianceZones.body.radius = 0;
		BlueAllianceZones.body.border.width = 0;
		BlueAllianceZones.text.color = LV_COLOR_MAKE(255, 255, 255);
	lv_obj_set_style(zone, &BlueAllianceZones);
}

void RedZones(lv_obj_t* zone, int w, int h, int x, int y){
	zone = lv_obj_create(AutonField, NULL);
	lv_obj_set_size(zone, w, h);//size
	lv_obj_align(zone, NULL, LV_ALIGN_IN_TOP_LEFT, x, y);//position
	lv_style_copy(&RedAllianceZones, &lv_style_plain);
		RedAllianceZones.body.main_color = LV_COLOR_RED;
		RedAllianceZones.body.grad_color = LV_COLOR_RED;
		RedAllianceZones.body.radius = 0;
		RedAllianceZones.body.border.width = 0;
		RedAllianceZones.text.color = LV_COLOR_MAKE(255, 255, 255);
	lv_obj_set_style(zone, &RedAllianceZones);
}

void Button(lv_obj_t* button, lv_obj_t* Page, int w, int h, int posx, int posy, lv_color32_t color/*Name, Page, Size, Position, Color, */){
	//button = lv_btn_create(Page, NULL); //creates button
	lv_obj_set_size(button, w, h); //sets button size
	lv_obj_align(button, NULL, LV_ALIGN_IN_TOP_LEFT, posx, posy);
	lv_style_copy(&ButtonPressed, &lv_style_plain);
	ButtonPressed.body.main_color = LV_COLOR_WHITE;
	ButtonPressed.body.grad_color = LV_COLOR_WHITE;
	ButtonPressed.body.radius = 0;
	ButtonPressed.text.color = LV_COLOR_BLACK;
	ButtonPressed.body.opa = AutonSelectPage;

	lv_style_copy(&ButtonReleased, &lv_style_plain);
    ButtonReleased.body.main_color = color;
    ButtonReleased.body.grad_color = color;
    ButtonReleased.body.radius = 0;
    ButtonReleased.text.color = LV_COLOR_BLACK;
	ButtonReleased.body.opa = AutonSelectPage;
	lv_btn_set_style(button, LV_BTN_STYLE_PR, &ButtonPressed);
	lv_btn_set_style(button, LV_BTN_STYLE_REL, &ButtonReleased);

	

}
static lv_res_t btn_click_action(lv_obj_t * btn)
{

    uint8_t id = lv_obj_get_free_num(btn); //id usefull when there are multiple buttons
	if(id ==0){//bakc button
		PageShown = false;
		AutonStart = 0;
		AutonomousMode = 0;
	}
	else if(id == 1)//Blue Team Roller
    { 
		PageShown = true;
		AutonStart = 1;
		
    }
	else if(id ==2){//Red Team No Roller

		PageShown = true;
		AutonStart = 2;
	}
	else if(id ==3){//Blue Team No Roller
		PageShown = true;
		AutonStart = 3;
	}
	else if(id ==4){//Red Team Roller
		PageShown = true;
		AutonStart = 4;
	}
	initialize();

    return LV_RES_OK;
}
void initialize() {
  if(PageShown == true){
    AutonSelectPage = 255;
  }
  else if (PageShown == false) {
    AutonSelectPage = 0;
  }
/*---------------GUI-----------------*/

	lv_style_copy(&BackButtonReleased, &lv_style_plain);
    BackButtonReleased.body.main_color = LV_COLOR_WHITE;
    BackButtonReleased.body.grad_color = LV_COLOR_WHITE;
    BackButtonReleased.body.radius = 0;
    BackButtonReleased.text.color = LV_COLOR_BLACK;
	BackButtonReleased.text.opa = AutonSelectPage;
	BackButtonReleased.body.opa = AutonSelectPage;

    lv_style_copy(&BackButtonPressed, &lv_style_plain);
    BackButtonPressed.body.main_color = LV_COLOR_GRAY;
    BackButtonPressed.body.grad_color =  LV_COLOR_GRAY;
    BackButtonPressed.body.radius = 0;
	BackButtonPressed.text.color = LV_COLOR_BLACK;
	BackButtonPressed.text.opa = AutonSelectPage;
	BackButtonPressed.body.opa = AutonSelectPage;

	lv_style_copy(&LabelStyle, &lv_style_plain);
	LabelStyle.text.color = LV_COLOR_WHITE;
	LabelStyle.text.opa = AutonSelectPage;
	//LabelStyle.text.opa = LabelShown;

    BackButton = lv_btn_create(lv_scr_act(), NULL); //create button, lv_scr_act() is deafult screen object
    lv_obj_set_free_num(BackButton, 0); //set button is to 0
   // lv_btn_set_action(BackButton, LV_BTN_ACTION_CLICK, btn_click_action); //set function to be called on button click
    lv_btn_set_style(BackButton, LV_BTN_STYLE_REL, &BackButtonReleased); //set the relesed style
    lv_btn_set_style(BackButton, LV_BTN_STYLE_PR, &BackButtonPressed); //set the pressed style
    lv_obj_set_size(BackButton, 80, 40); //set the button size
    lv_obj_align(BackButton, NULL, LV_ALIGN_IN_TOP_LEFT, 400, 0); //set the position to top mid
	lv_btn_set_action(BackButton, LV_BTN_ACTION_PR, btn_click_action);


    BackButtonLabel = lv_label_create(BackButton, NULL); //create label and puts it inside of the button
    lv_label_set_text(BackButtonLabel, "X"); //sets label text

	myLabel = lv_label_create(lv_scr_act(), NULL); //create label and puts it on the screen
    lv_label_set_text(myLabel, "Team or Solo"); //sets label text
    lv_obj_align(myLabel, NULL, LV_ALIGN_CENTER, -20, 0); //set the position to center
	lv_label_set_style(myLabel, &LabelStyle);

//Auton Page
	lv_style_copy(&FieldStyle, &lv_style_plain);
	FieldStyle.body.main_color = LV_COLOR_GRAY;
	FieldStyle.body.radius = 0;
	FieldStyle.body.border.width = 0;
	FieldStyle.body.grad_color = LV_COLOR_GRAY;
	lv_obj_set_size(AutonField, 480, 240);
	lv_page_set_style(AutonField, LV_PAGE_STYLE_BG, &FieldStyle);
	lv_page_set_sb_mode(AutonField, LV_SB_MODE_OFF);

//Solo or Team Page
	lv_style_copy(&SelectStyle, &lv_style_plain);
	SelectStyle.body.main_color = LV_COLOR_BLACK;
	SelectStyle.body.radius = 0;
	SelectStyle.body.border.width = 5;
	SelectStyle.body.border.color = LV_COLOR_WHITE;
	SelectStyle.body.border.opa = AutonSelectPage;
	SelectStyle.body.grad_color = LV_COLOR_BLACK;
	SelectStyle.body.opa = AutonSelectPage;
	SelectStyle.text.opa = AutonSelectPage;
	lv_page_glue_obj(TeamButton, true);
	lv_page_glue_obj(SoloButton, true);
	lv_page_set_sb_mode(AutonSelect, LV_SB_MODE_OFF);
	lv_obj_set_size(AutonSelect, 320, 160);
	lv_obj_align(AutonSelect,NULL,LV_ALIGN_IN_TOP_LEFT,90, 50);
	lv_page_set_style(AutonSelect, LV_PAGE_STYLE_BG, &SelectStyle);




/*--------------------------Doing the Buttons-------------------------------*/

/*---------------Auton Select-------------------*/

Button(TeamButton, AutonSelect, 240, 40, 40, 40, LV_COLOR_GRAY);
TeamLabel = lv_label_create(TeamButton, NULL);
lv_label_set_text(TeamLabel, "Team");
lv_label_set_style(TeamLabel, &SelectStyle);

Button(SoloButton, AutonSelect, 240, 40, 40, 100, LV_COLOR_GRAY);
SoloLabel = lv_label_create(SoloButton, NULL);
lv_label_set_text(SoloLabel, "Solo");
lv_label_set_style(SoloLabel, &SelectStyle);


/*-----------------------------------Field Zones--------------------------------------------*/
//Blue1
	lv_style_copy(&BlueButtonReleased, &lv_style_plain);
    BlueButtonReleased.body.main_color = LV_COLOR_BLUE;
    BlueButtonReleased.body.grad_color = LV_COLOR_BLUE;
    BlueButtonReleased.body.radius = 0;
	BlueButtonReleased.body.border.color = LV_COLOR_WHITE;
	BlueButtonReleased.body.border.width = 3;
    BlueButtonReleased.text.color = LV_COLOR_MAKE(255, 255, 255);

	lv_style_copy(&BlueButtonPressed, &lv_style_plain);
    BlueButtonPressed.body.main_color = LV_COLOR_WHITE;
    BlueButtonPressed.body.grad_color = LV_COLOR_WHITE;
    BlueButtonPressed.body.radius = 0;
    BlueButtonPressed.text.color = LV_COLOR_MAKE(255, 255, 255);


    lv_btn_set_style(BlueButton, LV_BTN_STYLE_REL, &BlueButtonReleased); //set the relesed style
    lv_btn_set_style(BlueButton, LV_BTN_STYLE_PR, &BlueButtonPressed); //set the pressed style
    lv_obj_set_size(BlueButton, 80, 40); //set the button size
	lv_obj_align(BlueButton, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 40); //set the position to top mid
	lv_obj_set_free_num(BlueButton, 1);
	lv_btn_set_action(BlueButton, LV_BTN_ACTION_PR, btn_click_action);
    lv_style_copy(&RedButtonReleased, &lv_style_plain);
    RedButtonReleased.body.main_color = LV_COLOR_RED;
    RedButtonReleased.body.grad_color = LV_COLOR_RED;
    RedButtonReleased.body.radius = 0;
	RedButtonReleased.body.border.color = LV_COLOR_WHITE;
	RedButtonReleased.body.border.width = 3;
    RedButtonReleased.text.color = LV_COLOR_MAKE(255, 255, 255);

    lv_style_copy(&RedButtonPressed, &lv_style_plain);
    RedButtonPressed.body.main_color = LV_COLOR_WHITE;
    RedButtonPressed.body.grad_color = LV_COLOR_WHITE;
    RedButtonPressed.body.radius = 0;
    RedButtonPressed.text.color = LV_COLOR_MAKE(255, 255, 255);

    lv_btn_set_style(RedButton, LV_BTN_STYLE_REL, &RedButtonReleased); //set the relesed style
    lv_btn_set_style(RedButton, LV_BTN_STYLE_PR, &RedButtonPressed); //set the pressed style
    lv_obj_set_size(RedButton, 80, 40); //set the button size
	lv_obj_align(RedButton, NULL, LV_ALIGN_IN_TOP_LEFT, 160, 0); //set the position to top mid
	lv_obj_set_free_num(RedButton, 2);
	lv_btn_set_action(RedButton, LV_BTN_ACTION_PR, btn_click_action);

//Blue2
    lv_btn_set_style(BlueButton2, LV_BTN_STYLE_REL, &BlueButtonReleased); //set the relesed style
    lv_btn_set_style(BlueButton2, LV_BTN_STYLE_PR, &BlueButtonPressed); //set the pressed style
    lv_obj_set_size(BlueButton2, 80, 40); //set the button size
	lv_obj_align(BlueButton2, NULL, LV_ALIGN_IN_TOP_LEFT, 240, 200); //set the position to top mid
	lv_obj_set_free_num(BlueButton2, 3);
	lv_btn_set_action(BlueButton2, LV_BTN_ACTION_PR, btn_click_action);
//Red2

    lv_btn_set_style(RedButton2, LV_BTN_STYLE_REL, &RedButtonReleased); //set the relesed style
    lv_btn_set_style(RedButton2, LV_BTN_STYLE_PR, &RedButtonPressed); //set the pressed style
    lv_obj_set_size(RedButton2, 80, 40); //set the button size
	lv_obj_align(RedButton2, NULL, LV_ALIGN_IN_TOP_LEFT, 400, 160); //set the position to top mid
	lv_obj_set_free_num(RedButton2, 4);
	lv_btn_set_action(RedButton2, LV_BTN_ACTION_PR, btn_click_action);




/*-----------DRAWING FIELD-------------*/ 
	// size 480 x 240
//Checker Pattern
Checkers(object, LV_COLOR_BLACK, 80, 0);
Checkers(object1, LV_COLOR_BLACK, 160, 40);
Checkers(object2, LV_COLOR_BLACK, 240, 80);
Checkers(object3, LV_COLOR_BLACK, 320, 120);
Checkers(object4, LV_COLOR_BLACK, 80, 80);
Checkers(object5, LV_COLOR_BLACK, 160, 120);
Checkers(object6, LV_COLOR_BLACK, 240, 160);
Checkers(object7, LV_COLOR_BLACK, 320, 40);
Checkers(object9, LV_COLOR_BLACK, 0, 200);
Checkers(object10, LV_COLOR_BLACK, 80, 160);
Checkers(object11, LV_COLOR_BLACK, 320, 200);
Checkers(object12, LV_COLOR_BLACK, 400, 0);


BlueZones(BlueZone1, 80, 80,  0, 80);
BlueZones(BlueZone2, 80, 40, 160, 200);
RedZones(RedZone1, 80, 40, 240, 0);
RedZones(RedZone2, 80, 80, 400, 80);


}









/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {

}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {

}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
if (AutonomousMode == 1){
	//auton 1: Team, Red, No Roller
}
else if (AutonomousMode ==2){
	//auton2: Team, Red, Roller
}
else if (AutonomousMode ==3){
	//auton3: Team, Blue, No Roller
}
else if (AutonomousMode ==4){
	//auton4: Team, Blue, Roller
}
else if (AutonomousMode ==5){
	//auton5: Solo, Red, No Roller
}
else if (AutonomousMode ==6){
	//auton6: Solo, Red, Roller
}
else if (AutonomousMode ==7){
	//auton7: Solo, Blue, No Roller
}
else if (AutonomousMode ==8){
	//auton8: Solo, Blue, Roller
}



}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {

pros::Controller master (E_CONTROLLER_MASTER);
while(true){
	if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
		AutonSelectPage = 255;
	}
	else{
		AutonSelectPage = 0;
	}
	pros::delay(20);
}



}
/*
void testArray(){
int array[6][6]; 
	for(int i = 0; i < 6; i++){
		for(int j = 0; j < 6; j++){
		array[i][j] = 200;
		cout << array[i][j];
	}
	}

}
*/