#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include "Btree.cpp"
#include<string.h>

//Button Definations
#define TWM_NEW 1
#define TWM_OPEN 2
#define TWM_EXIT 3
#define TWM_EDIT 4
#define TWM_TOOLS 5
#define TWM_SETTINGS 6
#define INSERT_BUTTON_PRESSED 7
#define SEARCH_BUTTON_PRESSED 8
#define LIST_BUTTON_PRESSED 9
#define EDIT_BUTTON_PRESSED 11
#define DELETE_BUTTON_PRESSED 12
#define EXIT_BUTTON_PRESSED 13
#define SAVE_BTN 14
#define SEARCH_BTN 15
#define DELETE_BTN 16
#define SAVE_BTN_EDIT 17
#define EDIT_SAVE_BTN 18



#define PADDING 10

void StartListWindow(HWND hwnd);
void DisplayGUIData(node *traversal);

userdata data1,data2;

//Function prototypes here
void addmenu(HWND);
void addcontrol(HWND);
void StartInsertWindow(HWND);
void StartSearchWindow(HWND);
void StartListWindow(HWND);
void startEditWindow(HWND);
void startExitWindow(HWND);
void startDeleteWindow(HWND);

//Global variables
HWND hViewWindow;
HWND hwnd;
HWND hViewControl;
int currentWindowIndex;

//handler for edit
HWND EditDIS,EditSearch,EditBTN,EditSaveBTN;

//for search
HWND hSearchContact;
HWND hSearchNumber;
HWND hSearchButton;
HWND hSearchResult;
HWND hSearchResultBox;


//HWND hwnd;
HWND hName,hNameDIS;
HWND hNumber,hNumberDIS;
HWND hAddress,hAddressDIS;
HWND hEmail,hEmailDIS;
HWND hSave,hSaveBTNDIS;
HWND hBackground;


HWND InsertAddStatic;


HWND hboxname1;
HWND hboxaddress1;
HWND hboxphone1;
HWND hboxemail1;

HWND hboxname;
HWND hboxaddress;
HWND hboxphone;
HWND hboxemail;

HWND hDeleteContact;
HWND hDeleteName;
HWND hDeleteEdit;
HWND hDeleteButton;

int width;
int height;

HWND hList;
HWND hNum;
HWND hListDIS;
HWND hListTitleDIS;


/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_INFORMATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_INFORMATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("Telephone Directory"),       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           800,                 /* The programs width */
           600,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    //fetch data from window;


    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);
    //for edit
    RECT rec;
    GetClientRect(hwnd, &rec);
    width = rec.right/20;
    height = rec.bottom/22;

       //for search
    hBackground = CreateWindowEx(0,"Static","",WS_CHILD|WS_BORDER|WS_VISIBLE, 3*width+20,5,17*width-30,22*height-10,hwnd,NULL,NULL,NULL);
    hSearchContact = CreateWindowEx(0, "static", "Search Contact", WS_CHILD | SS_CENTER, 7*width, rec.top+20,10*width, 30, hwnd, NULL, NULL, NULL);
    hSearchNumber = CreateWindowEx(0, "edit", "", WS_CHILD  | WS_BORDER, 5*width, 70, 11.5*width, 1.5*height,hwnd, NULL, NULL, NULL);
    hSearchButton = CreateWindowEx(0, "Button", "Search", WS_CHILD | WS_BORDER | ES_CENTER, 16*width,70,2*width,1.5*height,hwnd, (HMENU)SEARCH_BTN, NULL, NULL);
    hSearchResult = CreateWindowEx(0, "static", "Result", WS_CHILD  | WS_BORDER|SS_CENTER, 5*width, rec.top+140, 13*width, 28, hwnd, NULL, NULL, NULL);
    hSearchResultBox = CreateWindowEx(0, "static", "", WS_CHILD | WS_BORDER, 5*width, 165, 13*width, 12*height,hwnd, NULL, NULL, NULL);

    hboxname = CreateWindowEx(0, "static", "Name: ", WS_CHILD, 5.2*width, 170, 12.7*width, 30,hwnd, NULL, NULL, NULL);
    hboxaddress = CreateWindowEx(0, "static", "Address: ", WS_CHILD, 5.2*width, 200, 12.7*width, 30,hwnd, NULL, NULL, NULL);
    hboxphone = CreateWindowEx(0, "static", "Number: ", WS_CHILD , 5.2*width, 230, 12.7*width, 30,hwnd, NULL, NULL, NULL);
    hboxemail = CreateWindowEx(0, "static", "Email: ", WS_CHILD, 5.2*width, 260, 12.7*width, 30,hwnd, NULL, NULL, NULL);

    hboxname1 = CreateWindowEx(0, "static", "", WS_CHILD, 7*width, 170, 8.5*width, 30,hwnd, NULL, NULL, NULL);
    hboxaddress1 = CreateWindowEx(0, "static", "", WS_CHILD, 7*width, 200, 8.5*width, 30,hwnd, NULL, NULL, NULL);
    hboxphone1 = CreateWindowEx(0, "static", "", WS_CHILD , 7*width, 230, 8.5*width, 30,hwnd, NULL, NULL, NULL);
    hboxemail1 = CreateWindowEx(0, "static", "", WS_CHILD, 7*width, 260, 8.5*width, 30,hwnd, NULL, NULL, NULL);


    InsertAddStatic = CreateWindowEx(0,"static","ADD CONTACT +",WS_CHILD|SS_CENTER,width*8.5,20,10*width,23,hwnd,NULL,NULL,NULL);

    //for name
    hNameDIS = CreateWindowEx(0,"static","NAME",WS_CHILD|SS_CENTER,3.55*width,4.95*height,4*width,1*height,hwnd,NULL,NULL,NULL);
    hName = CreateWindowEx(0,"Edit","", WS_CHILD| WS_BORDER | ES_MULTILINE |ES_AUTOVSCROLL |ES_AUTOHSCROLL ,6.5*width,4.5*height,13*width,1.5*height,hwnd
                           ,NULL,NULL,NULL);

    //for number
    hNumberDIS = CreateWindowEx(0,"static","NUMBER",WS_CHILD|SS_CENTER,3.55*width,7.95*height,4*width,1*height,hwnd,NULL,NULL,NULL);
    hNumber = CreateWindowEx(0,"Edit","", WS_CHILD| WS_BORDER | ES_MULTILINE |ES_AUTOVSCROLL |ES_AUTOHSCROLL,6.5*width,7.5*height,13*width,1.5*height,hwnd,NULL,NULL,NULL);

    //for address
    hAddressDIS=CreateWindowEx(0,"static","ADDRESS",WS_CHILD|SS_CENTER,3.55*width,10.95*height,4*width,1*height,hwnd,NULL,NULL,NULL);
    hAddress = CreateWindowEx(0,"Edit","", WS_CHILD| WS_BORDER | ES_MULTILINE |ES_AUTOVSCROLL |ES_AUTOHSCROLL,6.5*width,10.5*height,13*width,1.5*height,hwnd,NULL,NULL,NULL);

    //for email
    hEmailDIS=CreateWindowEx(0,"static","EMAIL",WS_CHILD|SS_CENTER,3.55*width,13.95*height,4*width,1*height,hwnd,NULL,NULL,NULL);
    hEmail = CreateWindowEx(0,"Edit","", WS_CHILD| WS_BORDER | ES_MULTILINE |ES_AUTOVSCROLL |ES_AUTOHSCROLL,6.5*width,13.5*height,13*width,1.5*height,hwnd,NULL,NULL,NULL);

    //for save button
    hSaveBTNDIS=CreateWindowEx(0,"Button","SAVE", WS_CHILD| WS_BORDER,10*width,16.5*height,2.5*width,2*height,hwnd,(HMENU)SAVE_BTN,NULL,NULL);


    //for Delete
    hDeleteContact = CreateWindowEx(0,"Static","Delete Contact",WS_CHILD | SS_CENTER,7*width, rec.top+20,10*width, 30,hwnd,NULL,NULL,NULL);
    hDeleteName = CreateWindowEx(0,"Static","Name :",WS_CHILD,7*width, rec.top+55,10*width, 30,hwnd,NULL,NULL,NULL);
    hDeleteEdit = CreateWindowEx(0,"Edit","",WS_CHILD|WS_BORDER,7*width, rec.top+80,10*width, 30,hwnd,NULL,NULL,NULL);
    hDeleteButton = CreateWindowEx(0,"Button","Delete",WS_CHILD|WS_BORDER|SS_CENTER,7*width, rec.top+130,60, 30,hwnd,(HMENU)DELETE_BTN,NULL,NULL);


    //for Edit
    EditDIS = CreateWindowEx(0,"static","EDIT CONTACT",WS_CHILD|SS_CENTER,width*7,30,10*width,20,hwnd,NULL,NULL,NULL);
    EditSearch = CreateWindowEx(0,"Edit","",WS_CHILD|WS_BORDER|ES_MULTILINE|ES_AUTOVSCROLL|ES_AUTOHSCROLL,width*6.5,50,10*width,35,hwnd,NULL,NULL,NULL);
    EditBTN = CreateWindowEx(0, "Button", "Search", WS_CHILD | WS_BORDER | ES_CENTER,16.5*width,50,2.5*width,35,hwnd,(HMENU) SAVE_BTN_EDIT, NULL, NULL);
    EditSaveBTN=CreateWindowEx(0,"Button","SAVE", WS_CHILD| WS_BORDER,10*width,16.5*height,2.5*width,2*height,hwnd,(HMENU)EDIT_SAVE_BTN,NULL,NULL);


    hListTitleDIS = CreateWindowEx(0,"static","Contact List",WS_CHILD|SS_CENTER|WS_BORDER,3*PADDING+3*width,2*PADDING,17*width-5*PADDING,2*height-2*PADDING,hwnd,NULL,NULL,NULL);
    hListDIS = CreateWindowEx(0,"Static","  Name\t\t\t\t\t\t\tContact",WS_CHILD|WS_BORDER,3*PADDING+3*width,2*PADDING+2*height,17*width-5*PADDING,height,hwnd,NULL,NULL,NULL);
    hList = CreateWindowEx(0,"Listbox","",WS_CHILD|WS_BORDER|WS_VSCROLL,3*PADDING+3*width,2*PADDING+3*height,17*width-5*PADDING,18*height-5*PADDING,hwnd,NULL,NULL,NULL);
   // hNum = CreateWindowEx(0,"Listbox","",WS_CHILD|WS_BORDER|WS_VSCROLL,13*width-2*PADDING,2*PADDING+3*height,7*width,12*height-5*PADDING,hwnd,NULL,NULL,NULL);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    RECT rec;
    GetClientRect(hwnd,&rec);
    int width,height;
    switch (message)                  /* handle the messages */
    {
        case WM_CREATE:
            addmenu(hwnd);
            addcontrol(hwnd);
            strcpy(data1.name,"Alex");
            strcpy(data1.number,"1334");
            strcpy(data1.address,"ABC");
            strcpy(data1.email,"Alex@gmail.com");
            InsertData(data1);

            strcpy(data1.name,"Sam");
            strcpy(data1.number,"4444");
            strcpy(data1.address,"CBD");
            strcpy(data1.email,"Sam@gmail.com");
            InsertData(data1);
            strcpy(data1.name,"Anna");
            strcpy(data1.number,"87945");
            strcpy(data1.address,"SBB");
            strcpy(data1.email,"Anna@gmail.com");
            InsertData(data1);

            strcpy(data1.name,"George");
            strcpy(data1.number,"827193847");
            strcpy(data1.address,"ABC");
            strcpy(data1.email,"George@gmail.com");
            InsertData(data1);

            strcpy(data1.name,"Sophi");
            strcpy(data1.number,"3795799576");
            strcpy(data1.address,"BCD");
            strcpy(data1.email,"Sophi@gmail.com");
            InsertData(data1);

            strcpy(data1.name,"Hally");
            strcpy(data1.number,"173973984");
            strcpy(data1.address,"RST");
            strcpy(data1.email,"Hally@gmail.com");
            InsertData(data1);

            break;

        case WM_SIZE:
            switch(wParam) {
                case SIZE_MAXIMIZED:

                    width = rec.right/20;
                    height = rec.bottom/22;
                    SetWindowPos(hViewControl,0,10,10,3*width,22*height-10,SWP_NOMOVE|SWP_NOZORDER|SWP_NOACTIVATE);
                    SetWindowPos(hBackground,0,3*width+20,5,17*width-30,22*height-10,SWP_NOZORDER|SWP_NOACTIVATE);
            //        SetWindowPos(hViewWindow,0, 4*width,30, 10*width, 2.5*height,SWP_NOZORDER|SWP_NOACTIVATE);
                    switch(currentWindowIndex){
                        case 1:
                            StartInsertWindow(hViewWindow);
                            break;
                        case 2:
                            StartSearchWindow(hViewWindow);
                            break;


                    }
                    break;

                case SIZE_RESTORED:

                    width = rec.right/20;
                    height = rec.bottom/22;
                    SetWindowPos(hViewControl,0,10,10,3*width,22*height-10,SWP_NOMOVE|SWP_NOZORDER|SWP_NOACTIVATE);
                    SetWindowPos(hBackground,0,3*width+20,5,17*width-30,22*height-10,SWP_NOZORDER|SWP_NOACTIVATE);
                    switch(currentWindowIndex){
                        case 1:
                            StartInsertWindow(hViewWindow);
                            break;
                        case 2:
                            StartSearchWindow(hViewWindow);
                            break;


                    }
                    break;
            }
            break;

        case WM_COMMAND:
            switch(wParam)
            {
                case INSERT_BUTTON_PRESSED:
                    StartInsertWindow(hViewWindow);
                    break;

                case SEARCH_BUTTON_PRESSED:
                    StartSearchWindow(hViewWindow);
                    break;

                case LIST_BUTTON_PRESSED:
                    StartListWindow(hViewWindow);
                    break;

                case EDIT_BUTTON_PRESSED:
                    startEditWindow(hViewWindow);
                    break;

                case DELETE_BUTTON_PRESSED:
                    startDeleteWindow(hViewWindow);
                    break;

                case EXIT_BUTTON_PRESSED:
                    PostQuitMessage(0);
                    break;
                case TWM_EXIT:
                    PostQuitMessage(0);
                    break;

                case SAVE_BTN:
                    GetWindowText(hNumber,data1.number,50);
                    GetWindowText(hAddress,data1.address,20);
                    GetWindowText(hEmail,data1.email,50);
                    GetWindowText(hName,data1.name,30);
                    cout<<data1.number[3];
                    InsertData(data1);
                    SetWindowText(hName,"");
                    SetWindowText(hNumber,"");
                    SetWindowText(hAddress,"");
                    SetWindowText(hEmail,"");
                    break;

                case SEARCH_BTN:
                    char nam[50];
                    GetWindowText(hSearchNumber, nam, 20);
                    data1=SearchData(nam);
                    SetWindowText(hboxname1, data1.name);
                    SetWindowText(hboxaddress1, data1.address);
                    SetWindowText(hboxphone1, data1.number);
                    SetWindowText(hboxemail1, data1.email);
                    SetWindowText(hSearchNumber,"");
                    break;

                case DELETE_BTN:
                    char delname[20];
                    GetWindowText(hDeleteEdit, delname, 20);
                    DeleteData(delname);
                   /* if(1){
                        MessageBox(NULL,"DELETION SUCCESSFULL!!!", "Deletion", NULL);
                    }
                    else{
                        MessageBox(NULL, "DELETION UNSUCCESSFULL!!!", NULL, MB_ICONSTOP);
                    }*/
                    break;

                case SAVE_BTN_EDIT:
                    char editname[30];
                    GetWindowText(EditSearch,editname,30);
                    data1 = SearchData(editname);
                    SetWindowText(hName,data1.name);
                    SetWindowText(hNumber,data1.number);
                    SetWindowText(hAddress,data1.address);
                    SetWindowText(hEmail,data1.email);

                    break;
                case EDIT_SAVE_BTN:
                    char editnam[30];
                    GetWindowText(EditSearch,editnam,30);
                    data1 = SearchData(editnam);
                    GetWindowText(hName,data1.name,30);
                    GetWindowText(hNumber,data1.number,15);
                    GetWindowText(hAddress,data1.address,12);
                    GetWindowText(hEmail,data1.email,50);
                    InsertData(data1);
                    DeleteData(editnam);
                    SetWindowText(hName,"");
                    SetWindowText(hNumber,"");
                    SetWindowText(hAddress,"");
                    SetWindowText(hEmail,"");
                    //strcpy(data1.name,data2.name);
                    //strcpy(data1.number[3],data2.number[3]);
                    //strcpy(data1.address,data2.address);
                    //strcpy(data1.email,data2.email);

                    break;

                default:                      /* for messages that we don't deal with */
                    return DefWindowProc (hwnd, message, wParam, lParam);
            }
            break;

        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;

        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

//Menu

void addmenu(HWND hwnd){
    HMENU mainmenu = CreateMenu();
    HMENU filesubmenu = CreateMenu();

    //add data to main menu
    AppendMenu(mainmenu,MF_POPUP,(UINT_PTR)filesubmenu,"File");
    AppendMenu(mainmenu,MF_STRING,TWM_EDIT,"Edit");
    AppendMenu(mainmenu,MF_STRING,TWM_TOOLS,"Tools");
    AppendMenu(mainmenu,MF_STRING,TWM_SETTINGS,"Settings");

    //add data to file submenu
    AppendMenu(filesubmenu,MF_STRING,TWM_NEW,"New");
    AppendMenu(filesubmenu,MF_STRING,TWM_OPEN,"Open");
    AppendMenu(filesubmenu,MF_SEPARATOR,NULL,NULL);
    AppendMenu(filesubmenu,MF_STRING,TWM_EXIT,"Exit");

    //set menu bar
    SetMenu(hwnd,mainmenu);
}


//Global Controls

void addcontrol(HWND hwnd)
{
    RECT re;
    int height,width;
    GetClientRect(hwnd,&re);
    width = re.right/20;
    height = re.bottom/22;

    hViewControl = CreateWindowEx(0,"Static","",WS_CHILD|WS_VISIBLE|WS_BORDER,0,5,3*width,22*height-10,hwnd,NULL,NULL,NULL);
    CreateWindowEx(0,"Button","Insert",WS_CHILD|WS_VISIBLE|WS_BORDER,6,10,2.65*width,1.5*height,hwnd,(HMENU)INSERT_BUTTON_PRESSED,NULL,NULL);
    CreateWindowEx(0,"Button","Search",WS_CHILD|WS_VISIBLE|WS_BORDER,6,2.5*height,2.65*width,1.5*height,hwnd,(HMENU)SEARCH_BUTTON_PRESSED,NULL,NULL);
    CreateWindowEx(0,"Button","Edit",WS_CHILD|WS_VISIBLE|WS_BORDER,6,5*height,2.65*width,1.5*height,hwnd,(HMENU)EDIT_BUTTON_PRESSED,NULL,NULL);
    CreateWindowEx(0,"Button","Delete",WS_CHILD|WS_VISIBLE|WS_BORDER,6,7.5*height,2.65*width,1.5*height,hwnd,(HMENU)DELETE_BUTTON_PRESSED,NULL,NULL);
    CreateWindowEx(0,"Button","List",WS_CHILD|WS_VISIBLE|WS_BORDER,6,10*height,2.65*width,1.5*height,hwnd,(HMENU)LIST_BUTTON_PRESSED,NULL,NULL);
    CreateWindowEx(0,"Button","Exit",WS_CHILD|WS_VISIBLE|WS_BORDER,6,12.5*height,2.65*width,1.5*height,hwnd,(HMENU)EXIT_BUTTON_PRESSED,NULL,NULL);

   // hViewWindow = CreateWindowEx(0,"Static","",WS_CHILD|WS_BORDER,3*width+20,5,17*width-30,22*height-10,hwnd,NULL,NULL,NULL);

}

void StartInsertWindow(HWND hwnd)
{
    currentWindowIndex = 1;
    ShowWindow(InsertAddStatic,SW_SHOW);
    ShowWindow(hNameDIS,SW_SHOW);
    ShowWindow(hName,SW_SHOW);
    ShowWindow(hNumberDIS,SW_SHOW);
    ShowWindow(hNumber,SW_SHOW);
    ShowWindow(hAddressDIS,SW_SHOW);
    ShowWindow(hAddress,SW_SHOW);
    ShowWindow(hEmailDIS,SW_SHOW);
    ShowWindow(hEmail,SW_SHOW);
    ShowWindow(hSaveBTNDIS,SW_SHOW);


    ShowWindow(hSearchContact, SW_HIDE);
    ShowWindow(hSearchButton, SW_HIDE);
    ShowWindow(hSearchNumber, SW_HIDE);
    ShowWindow(hSearchResultBox, SW_HIDE);
    ShowWindow(hSearchResult, SW_HIDE);

    ShowWindow(hboxname, SW_HIDE);
    ShowWindow(hboxaddress, SW_HIDE);
    ShowWindow(hboxphone, SW_HIDE);
    ShowWindow(hboxemail, SW_HIDE);


    ShowWindow(hboxname1, SW_HIDE);
    ShowWindow(hboxaddress1, SW_HIDE);
    ShowWindow(hboxphone1, SW_HIDE);
    ShowWindow(hboxemail1, SW_HIDE);

    ShowWindow(hDeleteName, SW_HIDE);
    ShowWindow(hDeleteEdit, SW_HIDE);
    ShowWindow(hDeleteContact, SW_HIDE);
    ShowWindow(hDeleteButton, SW_HIDE);

    ShowWindow(EditDIS,SW_HIDE);
    ShowWindow(EditSearch,SW_HIDE);
    ShowWindow(EditBTN,SW_HIDE);
    ShowWindow(EditSaveBTN,SW_HIDE);

    ShowWindow(hListTitleDIS,SW_HIDE);
    ShowWindow(hList,SW_HIDE);
    ShowWindow(hListDIS,SW_HIDE);
    ShowWindow(hNum,SW_HIDE);
}

void StartSearchWindow(HWND hwnd)
{
    currentWindowIndex = 2;
    ShowWindow(hSearchButton, SW_SHOW);
    ShowWindow(hSearchContact, SW_SHOW);
    ShowWindow(hSearchNumber, SW_SHOW);
    ShowWindow(hSearchResult, SW_SHOW);
    ShowWindow(hSearchResultBox, SW_SHOW);

    ShowWindow(hboxname, SW_SHOW);
    ShowWindow(hboxaddress, SW_SHOW);
    ShowWindow(hboxphone, SW_SHOW);
    ShowWindow(hboxemail, SW_SHOW);

    ShowWindow(hboxname1, SW_SHOW);
    ShowWindow(hboxaddress1, SW_SHOW);
    ShowWindow(hboxphone1, SW_SHOW);
    ShowWindow(hboxemail1, SW_SHOW);


    ShowWindow(hDeleteName, SW_HIDE);
    ShowWindow(hDeleteEdit, SW_HIDE);
    ShowWindow(hDeleteContact, SW_HIDE);
    ShowWindow(hDeleteButton, SW_HIDE);

    ShowWindow(InsertAddStatic,SW_HIDE);
    ShowWindow(hNameDIS,SW_HIDE);
    ShowWindow(hName,SW_HIDE);
    ShowWindow(hNumberDIS,SW_HIDE);
    ShowWindow(hNumber,SW_HIDE);
    ShowWindow(hAddressDIS,SW_HIDE);
    ShowWindow(hAddress,SW_HIDE);
    ShowWindow(hEmailDIS,SW_HIDE);
    ShowWindow(hEmail,SW_HIDE);
    ShowWindow(hSaveBTNDIS,SW_HIDE);

    ShowWindow(EditDIS,SW_HIDE);
    ShowWindow(EditSearch,SW_HIDE);
    ShowWindow(EditBTN,SW_HIDE);
    ShowWindow(EditSaveBTN,SW_HIDE);

    ShowWindow(hListTitleDIS,SW_HIDE);
    ShowWindow(hList,SW_HIDE);
    ShowWindow(hListDIS,SW_HIDE);
    ShowWindow(hNum,SW_HIDE);
}

void StartListWindow(HWND hwnd)
{
    DisplayData(basepointer);
    currentWindowIndex = 4;
    SendMessage(hList,LB_RESETCONTENT,0,0);
    SendMessage(hNum,LB_RESETCONTENT,0,0);
    ShowWindow(hListTitleDIS,SW_SHOW);
    ShowWindow(hList,SW_SHOW);
    ShowWindow(hListDIS,SW_SHOW);
    ShowWindow(hNum,SW_SHOW);
    DisplayGUIData(basepointer);


     ShowWindow(InsertAddStatic,SW_HIDE);
    ShowWindow(hNameDIS,SW_HIDE);
    ShowWindow(hName,SW_HIDE);
    ShowWindow(hNumberDIS,SW_HIDE);
    ShowWindow(hNumber,SW_HIDE);
    ShowWindow(hAddressDIS,SW_HIDE);
    ShowWindow(hAddress,SW_HIDE);
    ShowWindow(hEmailDIS,SW_HIDE);
    ShowWindow(hEmail,SW_HIDE);
    ShowWindow(hSaveBTNDIS,SW_HIDE);


    ShowWindow(hSearchContact, SW_HIDE);
    ShowWindow(hSearchButton, SW_HIDE);
    ShowWindow(hSearchNumber, SW_HIDE);
    ShowWindow(hSearchResultBox, SW_HIDE);
    ShowWindow(hSearchResult, SW_HIDE);

    ShowWindow(hboxname, SW_HIDE);
    ShowWindow(hboxaddress, SW_HIDE);
    ShowWindow(hboxphone, SW_HIDE);
    ShowWindow(hboxemail, SW_HIDE);


    ShowWindow(hboxname1, SW_HIDE);
    ShowWindow(hboxaddress1, SW_HIDE);
    ShowWindow(hboxphone1, SW_HIDE);
    ShowWindow(hboxemail1, SW_HIDE);

    ShowWindow(hDeleteName, SW_HIDE);
    ShowWindow(hDeleteEdit, SW_HIDE);
    ShowWindow(hDeleteContact, SW_HIDE);
    ShowWindow(hDeleteButton, SW_HIDE);

    ShowWindow(EditDIS,SW_HIDE);
    ShowWindow(EditSearch,SW_HIDE);
    ShowWindow(EditBTN,SW_HIDE);
    ShowWindow(EditSaveBTN,SW_HIDE);
}

//2*PADDING+3*width,2*PADDING+2*height,17*width-4*PADDING,13*height-4*PADDING
void DisplayGUIData(node *traversal)
{
    if(traversal ==NULL){
        return;
    }
    int i;

    for(i = 0;i<=traversal->datanum;i++){
        if(!traversal->leafnode){
            DisplayGUIData(traversal->pointer[i]);
        }
        char display[150];
        display[95]='\0';
        strcpy(display,traversal->data[i].name);
        do
        {

            strcat(display,"-");

        }while(display[95]!='-');
        strcat(display,traversal->data[i].number);
        SendMessage(hList,LB_ADDSTRING,0,(LPARAM)display);
        //SendMessage(hNum,LB_ADDSTRING,0,(LPARAM)traversal->data[i].number);
    }
    if(!traversal->leafnode){
        DisplayGUIData(traversal->pointer[i]);
    }
}




void startEditWindow(HWND hwnd)
{
    ShowWindow(EditDIS,SW_SHOW);
    ShowWindow(EditSearch,SW_SHOW);
    ShowWindow(EditBTN,SW_SHOW);


    ShowWindow(hDeleteName, SW_HIDE);
    ShowWindow(hDeleteEdit, SW_HIDE);
    ShowWindow(hDeleteContact, SW_HIDE);
    ShowWindow(hDeleteButton, SW_HIDE);

    ShowWindow(InsertAddStatic,SW_HIDE);
    ShowWindow(hNameDIS,SW_SHOW);
    ShowWindow(hName,SW_SHOW);
    ShowWindow(hNumberDIS,SW_SHOW);
    ShowWindow(hNumber,SW_SHOW);
    ShowWindow(hAddressDIS,SW_SHOW);
    ShowWindow(hAddress,SW_SHOW);
    ShowWindow(hEmailDIS,SW_SHOW);
    ShowWindow(hEmail,SW_SHOW);
    ShowWindow(EditSaveBTN,SW_SHOW);
    ShowWindow(hSaveBTNDIS,SW_HIDE);

    ShowWindow(hSearchContact, SW_HIDE);
    ShowWindow(hSearchButton, SW_HIDE);
    ShowWindow(hSearchNumber, SW_HIDE);
    ShowWindow(hSearchResultBox, SW_HIDE);
    ShowWindow(hSearchResult, SW_HIDE);

    ShowWindow(hboxname, SW_HIDE);
    ShowWindow(hboxaddress, SW_HIDE);
    ShowWindow(hboxphone, SW_HIDE);
    ShowWindow(hboxemail, SW_HIDE);


    ShowWindow(hboxname1, SW_HIDE);
    ShowWindow(hboxaddress1, SW_HIDE);
    ShowWindow(hboxphone1, SW_HIDE);


    ShowWindow(hListTitleDIS,SW_HIDE);
    ShowWindow(hList,SW_HIDE);
    ShowWindow(hListDIS,SW_HIDE);
    ShowWindow(hNum,SW_HIDE);

}


void startDeleteWindow(HWND hwnd)
{
    ShowWindow(hDeleteName, SW_SHOW);
    ShowWindow(hDeleteEdit, SW_SHOW);
    ShowWindow(hDeleteContact, SW_SHOW);
    ShowWindow(hDeleteButton, SW_SHOW);

    ShowWindow(EditDIS,SW_HIDE);
    ShowWindow(EditSearch,SW_HIDE);
    ShowWindow(EditBTN,SW_HIDE);

    ShowWindow(hSearchContact, SW_HIDE);
    ShowWindow(hSearchButton, SW_HIDE);
    ShowWindow(hSearchNumber, SW_HIDE);
    ShowWindow(hSearchResultBox, SW_HIDE);
    ShowWindow(hSearchResult, SW_HIDE);

    ShowWindow(hboxname, SW_HIDE);
    ShowWindow(hboxaddress, SW_HIDE);
    ShowWindow(hboxphone, SW_HIDE);
    ShowWindow(hboxemail, SW_HIDE);

    ShowWindow(hboxname1, SW_HIDE);
    ShowWindow(hboxaddress1, SW_HIDE);
    ShowWindow(hboxphone1, SW_HIDE);
    ShowWindow(hboxemail1, SW_HIDE);

    ShowWindow(InsertAddStatic,SW_HIDE);
    ShowWindow(hNameDIS,SW_HIDE);
    ShowWindow(hName,SW_HIDE);
    ShowWindow(hNumberDIS,SW_HIDE);
    ShowWindow(hNumber,SW_HIDE);
    ShowWindow(hAddressDIS,SW_HIDE);
    ShowWindow(hAddress,SW_HIDE);
    ShowWindow(hEmailDIS,SW_HIDE);
    ShowWindow(hEmail,SW_HIDE);
    ShowWindow(hSaveBTNDIS,SW_HIDE);
    ShowWindow(EditSaveBTN,SW_HIDE);
    ShowWindow(hListTitleDIS,SW_HIDE);
    ShowWindow(hList,SW_HIDE);
    ShowWindow(hListDIS,SW_HIDE);
    ShowWindow(hNum,SW_HIDE);

}
