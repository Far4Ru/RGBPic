#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define TEMP "temp" // временное имя файла назначения
#define FILE_LENGTH_MAX 255 // длина имени обрабатываемого файла
#define ID_MYBUTTON 1 // идентификатор для кнопочки внутри главного окна, определяем этот идентификатор как единицу 
#define ID_MYEDIT 1

char* concat(char *s1, char *s2) {

	size_t len1 = strlen(s1);
	size_t len2 = strlen(s2);                      

	char *result = malloc(len1 + len2 + 1);

	if (!result) {
		fprintf(stderr, "malloc() failed: insufficient memory!\n");
		return NULL;
	}

	memcpy(result, s1, len1);
	memcpy(result + len1, s2, len2 + 1);    

	return result;
}

LRESULT CALLBACK MainWinProc(HWND,UINT,WPARAM,LPARAM);


int WINAPI WinMain(HINSTANCE hInst,  HINSTANCE qwe,LPSTR qwer, int ss) 
{     /* */
	/* создаем и регистрируем класс главного окна */
	 /* это си код , с использованием структур - читай учебник по си, если 
	  не знаешь что это такое*/
	WNDCLASS wc; /*объявляем наш класс*/
	wc.style=0; /* стиль (поведение) класса окон,*/
	wc.lpfnWndProc=MainWinProc; /*процедура обработки событий окна - передаём указатель на функцуию*/
	wc.cbClsExtra=0; /*размер дополнительной памяти в системной структуре класса для данных пользователя */
	wc.cbWndExtra=0; /*  размер дополнительной памяти в системной структуре окна для данных пользователя*/
	wc.hInstance=hInst;/*дескриптор модуля (экземпляра программы), в котором реализована процедура обработки - передаём указатель на нашу программу ,полученный из WinMain() */
	wc.hIcon=NULL; /* дескриптор иконки окна*/
	wc.hCursor=NULL; /*дескриптор курсора мыши для окна */
	wc.hbrBackground=(HBRUSH)(COLOR_WINDOW+1);/* дескриптор "кисточки" для закрашивания фона окна - определяем стиль закрашивания*/
	wc.lpszMenuName=NULL;/* имя ресурса, содержащего меню окна*/
	wc.lpszClassName="Example_code_win_api_on_c_realization_simple";/* имя класса*/
	if (!RegisterClass(&wc)) return FALSE; /*  регистрируем класс программы с заполненной структорой  -в случае деуспешности последнего действа -
										  возвращаем "наружу" всеми признанный идентификатор неуспешности - false*/

										   
	/* создаем главное окно и отображаем его  - передаём 11 параметров*/
	HWND hMainWnd=CreateWindow("Example_code_win_api_on_c_realization_simple", /*имя класса  */
	"EXAMPLE WIN API C",/*имя окна (заголовок) */
	WS_OVERLAPPEDWINDOW, /*стиль (поведение) окна =  стиль WS_OVERLAPPEDWINDOW дарует окну стандартные в числе прочего 
						стандартные кнопки свёртывания - развёртывания и заголовок */
	/*CW_USEDEFAULT - этот параметр предлагает операционной системе виндоус самой определиться со значением ниже 
	 перечисленных характеристик окна.*/
	 CW_USEDEFAULT, /*горизонтальная позиция окна на экране -  точка левого верхнего угла окна - х-координата  */
	 CW_USEDEFAULT, /*вертикальная позиция окна на экране -  точка левого верхнего угла окна - у-координата  - от нее откладываются длина и высота*/
	 CW_USEDEFAULT, /*ширина окна */
	 CW_USEDEFAULT, /*высота окна */
	 NULL, /*дескриптор родительского окна */
	 NULL, /*дескриптор меню */
	 hInst, /* дескриптор экземпляра программы */
	 NULL /*указатель на какую-нибудь ерунду (по другой версии - "указатель на данные создания окна")*/
	 );

	if (!hMainWnd) return FALSE;  /* если создать окно почему-то не удалось   - не станем скрывать это!))*/
	 
	ShowWindow(hMainWnd,ss); /*  показывает окно, использует только что заполненную стурктуру окна и,
							   в качестве второго параметра - переменну полученную от системы через WinMain(),
							   которая дополнительно описывает формат опять же окна.
								 */
	UpdateWindow(hMainWnd);  /* Модифицирует клиентскую область окна*/

	MSG msg; 
	/* цикл обработки событий */
	while (GetMessage(&msg,NULL,0,0)) 
	{
		 TranslateMessage(&msg); 
		 DispatchMessage(&msg); 
	} 
	return msg.wParam; 
}

/* процедура обработки сообщений для главного окна */
LRESULT CALLBACK MainWinProc(HWND hw,UINT msg,WPARAM wp,LPARAM lp) {
	switch (msg) 
	{
		 case WM_CREATE:
				CreateWindow("edit","EDIT",WS_CHILD|WS_VISIBLE,
			   5,5,100,20,hw,(HMENU)ID_MYEDIT,NULL,NULL);
			  /* при создании окна внедряем в него кнопочку */
			  CreateWindow("button","BUTTON",WS_CHILD|BS_PUSHBUTTON|WS_VISIBLE,
			   100,200,100,20,hw,(HMENU)ID_MYBUTTON,NULL,NULL);
			  /* стиль WS_CHILD означает, что это дочернее окно и для него
			   вместо дескриптора меню будет передан целочисленный идентификатор,
			   который будет использоваться дочерним окном для оповещения 
			   родительского окна через WM_COMMAND */
			  return 0;
		 case WM_COMMAND:
			  /* нажата наша кнопочка? */
			  if ((HIWORD(wp)==0) && (LOWORD(wp)==ID_MYEDIT)) 
			   MessageBox(hw,"Message!","Edit",MB_OK|MB_ICONWARNING);
			  if ((HIWORD(wp)==0) && (LOWORD(wp)==ID_MYBUTTON)) 
			   MessageBox(hw,"Button is pressed","Button",MB_OK|MB_ICONWARNING);
			  return 0;
		 case WM_DESTROY:
			  /* пользователь закрыл окно, программа может завершаться */
			  PostQuitMessage(0);
			  return 0;
	}
	return DefWindowProc(hw,msg,wp,lp);
}
/*int main(){
	//Ввести имя файла
	//..
	//char * filename = "image.bmp";
	puts( "File name:" );
    char filename[ FILE_LENGTH_MAX ];
    gets( filename );
	//Проверить на наличие
	//..
	
	FILE *f = fopen(filename, "rb+");
	if (filename == NULL ) {
        perror( "Error file open" );
        return EXIT_FAILURE;
    }
	int w = 0, h = 0, d = 0;
	fseek(f, 18, SEEK_SET);
	fread(&w, sizeof(w), 1, f);
	fread(&h, sizeof(h), 1, f);
	fseek(f, 2, SEEK_CUR);
	fread(&d, 2, 1, f);
	printf("File info: %s %d %d %d\n", filename, w, h, d);
	int **m=(int**)malloc(h*sizeof(int**)),i,j;
	//Номер
	int fileNum = 0;
	fileNum++;
	
	//fclose(new_f);
	FILE* new_f = fopen( TEMP, "wb+" ); // пытаемся создать и открыть файл назначения для записи
    // обрабатываем ошибку открытия файла
    if ( new_f == NULL ) {
        perror( "Error create file" );
        return EXIT_FAILURE;
    }
	
	fclose(new_f);
	
	fclose(f);
	char *new_filename = concat(strtok (filename,"."), "_new.bmp");
	for(i=0;i<h;i++){
		m[i]=(int*)malloc(w*sizeof(int));
		for(j=0;j<w;j++){
			//
		}
	}
	//new_filename = sprintf(new_filename, "%d", fileNum );
	// удаляем исходный файл и переименовываем файл назначения - даем ему имя исходного файла
    if (rename(TEMP, new_filename ) == 0 )
		printf("Created %s\n", new_filename);
    else{
        perror( "Error processing" );
        return EXIT_FAILURE;
    }
    free(new_filename);
	
	//loop
	//while(1);
	
	return 0;
}*/