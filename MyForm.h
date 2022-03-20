#pragma once
#include "Polygon.h"
#include <cmath>
#include <fstream>
#include <string.h>



namespace SplittingPolygon {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	
	//форма с приветсвенным сообщением
	public ref class MyMessageBox : public System::Windows::Forms::Form
	{
	public:
		MyMessageBox(void)
		{
			InitializeComponent();
		}

	private:

		Button^ buttonStart; 
		TextBox^ text; 

		void InitializeComponent(void) 
		{
			this->ClientSize = System::Drawing::Size(504, 220);
			this->Text = L"Разбиение невыпуклого многоугольника";
			this->StartPosition = FormStartPosition::CenterScreen;

			//кнопка "Начать"
			buttonStart = gcnew Button();
			buttonStart->Location = System::Drawing::Point(this->ClientSize.Width * 0.4, this->ClientSize.Height * 0.75);
			buttonStart->Size = System::Drawing::Size(this->ClientSize.Width * 0.2, this->ClientSize.Height * 0.15);
			buttonStart->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", (float)(this->ClientSize.Height * 0.05), System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			buttonStart->Text = "Начать";
			buttonStart->UseVisualStyleBackColor = true;
			buttonStart->TabStop = false; //убирает фокус (синее выделение) с кнопки
			this->Controls->Add(buttonStart);

			//приветственное сообщение
			text = gcnew TextBox();
			text->Location = System::Drawing::Point(this->ClientSize.Width * 0.1, this->ClientSize.Height * 0.1);
			text->Size = System::Drawing::Size(this->ClientSize.Width * 0.8, this->ClientSize.Height * 0.7);
			text->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", (float)(this->ClientSize.Height * 0.06), System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			text->Text = "Добро пожаловать!\r\n Пожалуйста, вводите координаты точек по порядку по часовой стрелке\r\n  \n" +
				"(обратите внимание, что десятичные дроби вводятся в руссифицированном формате - через запятую)";
			text->Multiline = true;
			text->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			text->BackColor = this->BackColor;
			text->BorderStyle = BorderStyle::None;
			text->TabStop = false;
			this->Controls->Add(text);

			this->buttonStart->Click += gcnew System::EventHandler(this, &MyMessageBox::buttonStart_Click);
		}

		void buttonStart_Click(System::Object^ sender, System::EventArgs^ e) {
			this->Close();
		}
	};

	//форма с вопросом о сохранении результата в файл
	public ref class MyQuestion : public System::Windows::Forms::Form {
	public:
		MyQuestion(void)
		{
			InitializeComponent();
		}

	private:
		Button^ buttonYes; //кнопка "Да"
		Button^ buttonNo; //кнопка "Нет"
		TextBox^ questionBox; //текст вопроса
		TextBox^ filenameBox; //поле под имя файла
		TextBox^ extension; //расширение файла
		Button^ continueBut; //кнопка "Продолжить"
	protected:
		
		void InitializeComponent(void)
		{
			this->ClientSize = System::Drawing::Size(450, 120);
			this->Text = L"Разбиение невыпуклого многоугольника";
			this->StartPosition = FormStartPosition::CenterScreen;

			//вопрос о сохранении
			questionBox = gcnew TextBox();
			questionBox->Location = System::Drawing::Point(this->ClientSize.Width * 0.1, this->ClientSize.Height * 0.1);
			questionBox->Size = System::Drawing::Size(this->ClientSize.Width * 0.8, this->ClientSize.Height * 0.5);
			questionBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", (float)(this->ClientSize.Height * 0.1), System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			questionBox->Text = "Вы хотите сохранить файл с координатами вершин многоугольников, полученных в результате разбиения?";
			questionBox->Multiline = true;
			questionBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			questionBox->BackColor = this->BackColor;
			questionBox->BorderStyle = BorderStyle::None;
			questionBox->TabStop = false;
			this->Controls->Add(questionBox);

			//кнопка "Да"
			buttonYes = gcnew Button();
			buttonYes->Location = System::Drawing::Point(this->ClientSize.Width * 0.25, this->ClientSize.Height * 0.7);
			buttonYes->Size = System::Drawing::Size(this->ClientSize.Width * 0.2, this->ClientSize.Height * 0.25);
			buttonYes->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", (float)(this->ClientSize.Height * 0.1), System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			buttonYes->Text = "Да";
			buttonYes->UseVisualStyleBackColor = true;
			buttonYes->TabStop = false; //убирает фокус (синее выделение) с кнопки
			this->Controls->Add(buttonYes);
			this->buttonYes->Click += gcnew System::EventHandler(this, &MyQuestion::buttonYes_Click);

			//кнопка "Нет"
			buttonNo = gcnew Button();
			buttonNo->Location = System::Drawing::Point(this->ClientSize.Width * 0.55, this->ClientSize.Height * 0.7);
			buttonNo->Size = System::Drawing::Size(this->ClientSize.Width * 0.2, this->ClientSize.Height * 0.25);
			buttonNo->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", (float)(this->ClientSize.Height * 0.1), System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			buttonNo->Text = "Нет";
			buttonNo->UseVisualStyleBackColor = true;
			buttonNo->TabStop = false; //убирает фокус (синее выделение) с кнопки
			this->Controls->Add(buttonNo);
			this->buttonNo->Click += gcnew System::EventHandler(this, &MyQuestion::buttonNo_Click);

			//поле "имя файла"
			filenameBox = gcnew TextBox();
			filenameBox->Location = System::Drawing::Point(this->ClientSize.Width * 0.2, this->ClientSize.Height * 0.3);
			filenameBox->Size = System::Drawing::Size(this->ClientSize.Width * 0.54, this->ClientSize.Height * 0.2);
			filenameBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", (float)(this->ClientSize.Height * 0.1), System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			filenameBox->Multiline = true;
			filenameBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			filenameBox->TabStop = false;

			//расширение
			extension = gcnew TextBox();
			extension->Location = System::Drawing::Point(this->ClientSize.Width * 0.745, this->ClientSize.Height * 0.3);
			extension->Size = System::Drawing::Size(this->ClientSize.Width * 0.2, this->ClientSize.Height * 0.2);
			extension->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", (float)(this->ClientSize.Height * 0.1), System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			extension->TextAlign = System::Windows::Forms::HorizontalAlignment::Left;
			extension->Text = ".txt";
			extension->TabStop = false;
			extension->BackColor = this->BackColor;
			extension->BorderStyle = BorderStyle::None;

			//кнопка "продолжить"
			continueBut = gcnew Button();
			continueBut->Location = System::Drawing::Point(this->ClientSize.Width * 0.35, this->ClientSize.Height * 0.7);
			continueBut->Size = System::Drawing::Size(this->ClientSize.Width * 0.3, this->ClientSize.Height * 0.25);
			continueBut->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", (float)(this->ClientSize.Height * 0.1), System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			continueBut->Text = "Продолжить";
			continueBut->UseVisualStyleBackColor = true;
			continueBut->TabStop = false; //убирает фокус (синее выделение) с кнопки
			this->continueBut->Click += gcnew System::EventHandler(this, &MyQuestion::continueBut_Click);
		}
		
		void buttonNo_Click(System::Object^ sender, System::EventArgs^ e) {
			remove("output.txt");
			this->Close();
		}

		void buttonYes_Click(System::Object^ sender, System::EventArgs^ e) {

			this->Controls->Remove(buttonNo);
			this->Controls->Remove(buttonYes);
			questionBox->Text = "Введите имя файла для сохранения:";
			questionBox->Size = System::Drawing::Size(this->ClientSize.Width * 0.8, this->ClientSize.Height * 0.2);
			this->Controls->Add(filenameBox);
			this->Controls->Add(extension);
			this->Controls->Add(continueBut);

		}

		void continueBut_Click(System::Object^ sender, System::EventArgs^ e) {
			using namespace Runtime::InteropServices;
			filenameBox->Text += ".txt";
			const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(filenameBox->Text)).ToPointer();
			rename("output.txt", chars);
			this->Close();
		}
	};

	//форма с вопросом о направлении 
	public ref class MyAxes: public System::Windows::Forms::Form
	{
	public:
		MyAxes(void)
		{
			InitializeComponent();
		}

	private:
		TextBox^ questionBox; //вопрос об осях
		Button^ buttonUp; //кнопка "ось вверх"
		Button^ buttonDown; //кнопка "ось вниз"
		bool* thisUp; //истина, если ось вверх

	protected:
		void InitializeComponent(void) {

			this->ClientSize = System::Drawing::Size(504, 400);
			this->Text = L"Разбиение невыпуклого многоугольника";
			this->StartPosition = FormStartPosition::CenterScreen;

			//вопрос о направлении осей
			questionBox = gcnew TextBox();
			questionBox->Location = System::Drawing::Point(this->ClientSize.Width * 0.1, this->ClientSize.Height * 0.05);
			questionBox->Size = System::Drawing::Size(this->ClientSize.Width * 0.8, this->ClientSize.Height * 0.1);
			questionBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", (float)(this->ClientSize.Height * 0.05), System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			questionBox->Text = "Как направить оси?";
			questionBox->Multiline = true;
			questionBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			questionBox->BackColor = this->BackColor;
			questionBox->BorderStyle = BorderStyle::None;
			questionBox->TabStop = false;
			this->Controls->Add(questionBox);


			Resources::ResourceManager^ rm = gcnew Resources::ResourceManager("SplittingPolygonProject.Resources", Reflection::Assembly::GetExecutingAssembly());

			//кнопка "ось вверх"
			buttonUp = gcnew Button();
			buttonUp->Location = System::Drawing::Point(this->ClientSize.Width * 0.1, this->ClientSize.Height * 0.2);
			buttonUp->Size = System::Drawing::Size(this->ClientSize.Width * 0.35, this->ClientSize.Height * 0.7);
			buttonUp->BackgroundImage = safe_cast<System::Drawing::Bitmap^>(rm->GetObject("pictureUp"));
			buttonUp->BackgroundImageLayout = ImageLayout::Zoom;
			buttonUp->TabStop = false;
			this->Controls->Add(buttonUp);
			this->buttonUp->Click += gcnew System::EventHandler(this, &MyAxes::buttonUp_Click);

			//кнопка "ось вниз"
			buttonDown = gcnew Button();
			buttonDown->Location = System::Drawing::Point(this->ClientSize.Width * 0.55, this->ClientSize.Height * 0.2);
			buttonDown->Size = System::Drawing::Size(this->ClientSize.Width * 0.35, this->ClientSize.Height * 0.7);
			buttonDown->BackgroundImage = safe_cast<System::Drawing::Bitmap^>(rm->GetObject(L"pictureDown"));
			buttonDown->BackgroundImageLayout = ImageLayout::Zoom;
			buttonDown->TabStop = false;
			this->Controls->Add(buttonDown);
			this->buttonDown->Click += gcnew System::EventHandler(this, &MyAxes::buttonDown_Click);
		}

		void buttonUp_Click(System::Object^ sender, System::EventArgs^ e) {
			del(true);
			this->Close();
		}

		void buttonDown_Click(System::Object^ sender, System::EventArgs^ e) {
			del(false);
			this->Close();
		}
		
	public: delegate void Delegate(bool Up);
	public: Delegate^ del; 
	};

	//основная форма
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:

		MyForm(void)
		{
			InitializeComponent();
			Message(); //вывод приветсвенного сообщения
		}

	protected:
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		System::ComponentModel::Container^ components;
		TextBox^ numberX; //поле под координату X
		TextBox^ numberY; //поле под координату Y

		Polygon^ polygon; //многоугольник

		Button^ buttonAdd; //кнопка "Добавить точку"
		TextBox^ message; //сообщение о неправильном вводе
		Timer^ timer; //таймер, по которому сообщение исчезнет

		Button^ buttonFile; //кнопка "Ввести из файла"
		TextBox^ textFile; //под название файла
		Button^ butOk; //подтверждение ввода из файла

		Button^ buttonDraw; //кнопка "Построить многоугольник"
		Button^ buttonSplitting; //кнопка "Разбить многоугольник"

		Button^ buttonNewPolygon; //кнопка "Новый многоугольник"

		//для масштабирования изображения многоугольника
		double streching = 0; //растяжение по осям
		int shiftX; //сдвиг по X для центровки
		int shiftY; //сдвиг по Y для центровки
		double maxX; //для расчета предыдущих значений
		double minX;
		double maxY;
		double minY;

		char factor = -1; //так как расчет ведется с осью OY вниз, если пользователь выбрал "вверх" координаты по Y домножаются на -1, что устанавливает соответствие между этими системами

		//параметры поля для рисования
		int xRect;
		int yRect;
		int widthRect;
		int heightRect;

		//нужны при изменении размеров формы для корректной отрисовки
		bool visible; //многоугольник построен
		bool split; //многоугольник разбит

		IO::StreamWriter^ fout; //вывод результата в файл

	protected:

		//старт программы - отрисовка формы, вопрос об осях
		void Form_Shown(System::Object^ sender, System::EventArgs^ e) {
			Draw();
			MyAxes^ axeBox = gcnew MyAxes();
			axeBox->del = gcnew MyAxes::Delegate(this, &MyForm::axeUp);
			axeBox->ShowDialog();
		}

		//вывоз формы приветственного сообщения
		void Message() { //вызов формы с приветственным сообщением
			MyMessageBox^ msgBox = gcnew MyMessageBox();
			msgBox->ShowDialog();
		}

		//отрисовка основной формы
		void Draw() { //отрисовка кпопок и полей ввода

			int left = this->ClientSize.Width * 0.7; //левая координата большинства объектов

			int sizeOfText; //размер шрифта на элементах
			if ((this->ClientSize.Height * 0.02) < (this->ClientSize.Width * 0.016)) sizeOfText = (this->ClientSize.Height * 0.02);
			else sizeOfText = (this->ClientSize.Width * 0.016);

			//окно с текстом X=
			TextBox^ textX = gcnew TextBox();
			textX->Location = System::Drawing::Point(left, this->ClientSize.Height * 0.205);
			textX->Size = System::Drawing::Size(this->ClientSize.Width * 0.03, this->ClientSize.Height * 0.05);
			textX->TextAlign = HorizontalAlignment::Right;
			textX->Text = "X =";
			textX->BackColor = this->BackColor;
			textX->BorderStyle = BorderStyle::None;
			textX->TabStop = false;
			this->Controls->Add(textX);

			//окно с текстом Y=
			TextBox^ textY = gcnew TextBox();
			textY->Location = System::Drawing::Point(left, this->ClientSize.Height * 0.255);
			textY->Size = System::Drawing::Size(this->ClientSize.Width * 0.03, this->ClientSize.Height * 0.05);
			textY->TextAlign = HorizontalAlignment::Right;
			textY->Text = "Y =";
			textY->BackColor = this->BackColor;
			textY->BorderStyle = BorderStyle::None;
			textY->TabStop = false;
			this->Controls->Add(textY);

			//кнопка "Ввести из файла"
			buttonFile->Location = System::Drawing::Point(left, this->ClientSize.Height * 0.42);
			buttonFile->Size = System::Drawing::Size(this->ClientSize.Width * 0.23, this->ClientSize.Height * 0.055);
			buttonFile->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", sizeOfText, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			buttonFile->Text = "Ввести из файла";
			buttonFile->TabStop = false;
			this->Controls->Add(buttonFile);

			//кнопка "Построить многоугольник"
			buttonDraw->Location = System::Drawing::Point(left, this->ClientSize.Height * 0.55);
			buttonDraw->Size = System::Drawing::Size(this->ClientSize.Width * 0.23, this->ClientSize.Height * 0.1);
			buttonDraw->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", sizeOfText, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			buttonDraw->Text = "Построить\n многоугольник";
			buttonDraw->TabStop = false;
			this->Controls->Add(buttonDraw);

			//кнопка "Разбить многоугольник"
			buttonSplitting->Location = System::Drawing::Point(left, this->ClientSize.Height * 0.7);
			buttonSplitting->Size = System::Drawing::Size(this->ClientSize.Width * 0.23, this->ClientSize.Height * 0.1);
			buttonSplitting->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", sizeOfText, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			buttonSplitting->Text = "Разбить\n многоугольник";
			buttonSplitting->TabStop = false;
			this->Controls->Add(buttonSplitting);

			//сообщение
			message = gcnew TextBox();
			message->Location = System::Drawing::Point(left, this->ClientSize.Height * 0.07);
			message->Size = System::Drawing::Size(this->ClientSize.Width * 0.25, this->ClientSize.Height * 0.08);
			message->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 1.25 * sizeOfText, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			message->BackColor = this->BackColor;
			message->BorderStyle = BorderStyle::None;
			message->TabStop = false;
			message->TextAlign = HorizontalAlignment::Center;
			message->Multiline = true;

			left = this->ClientSize.Width * 0.74;

			//окно для ввода данных X
			numberX = gcnew TextBox();
			numberX->Location = System::Drawing::Point(left, this->ClientSize.Height * 0.2);
			numberX->Size = System::Drawing::Size(this->ClientSize.Width * 0.15, this->ClientSize.Height * 0.05);
			textX->TabStop = false;
			this->Controls->Add(numberX);

			//окно для ввода данных Y
			numberY = gcnew TextBox();
			numberY->Location = System::Drawing::Point(left, this->ClientSize.Height * 0.25);
			numberY->Size = System::Drawing::Size(this->ClientSize.Width * 0.15, this->ClientSize.Height * 0.05);
			textX->TabStop = false;
			this->Controls->Add(numberY);

			//кнопка "Добавить точку"
			buttonAdd->Location = System::Drawing::Point(left, this->ClientSize.Height * 0.3);
			buttonAdd->Size = System::Drawing::Size(this->ClientSize.Width * 0.15, this->ClientSize.Height * 0.1);
			buttonAdd->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", sizeOfText, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			buttonAdd->Text = "Добавить\n точку";
			this->Controls->Add(buttonAdd);

			buttonNewPolygon->Location = System::Drawing::Point(this->ClientSize.Width * 0.4, this->ClientSize.Height * 0.88);
			buttonNewPolygon->Size = System::Drawing::Size(this->ClientSize.Width * 0.2, this->ClientSize.Height * 0.1);
			buttonNewPolygon->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", sizeOfText, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			buttonNewPolygon->Text = "Новый многоугольник";
			this->Controls->Add(buttonNewPolygon);

			//область для рисования
			Graphics^ gr = this->CreateGraphics();
			xRect = 0.05 * this->ClientSize.Width;
			yRect = 0.05 * this->ClientSize.Height;
			widthRect = 0.6 * this->ClientSize.Width;
			heightRect = 0.8 * this->ClientSize.Height;
			Brush^ brush = gcnew SolidBrush(Color::White);
			gr->FillRectangle(brush, xRect, yRect, widthRect, heightRect);
		}

		//"Добавить точку"
		void buttonAdd_Click(System::Object^ sender, System::EventArgs^ e) {

			double X, Y;

			bool error = false;
			try
			{
				X = Convert::ToDouble(numberX->Text);
				Y = Convert::ToDouble(numberY->Text);
			}
			catch (...)
			{
				error = true;
				message->ForeColor = Color::Red;
				message->Text = "Недопустимый ввод!"; //предупреждающее сообщение
				this->Controls->Add(message);
				timer->Interval = 2000;
				timer->Start();
			}

			if (!error) { //если данные введены корректно
				polygon->AddPoint(X, factor * Y); //добавляем в многоугольник с учетом направления оси
				if (Controls->Contains(message)) { //если до этого была ошибка
					message->ForeColor = Color::Green;
					message->Text = "Спасибо :)";
					this->Controls->Add(message);
					timer->Interval = 1000;
					timer->Start();
				}

			}

		}
		void timer_Tick(System::Object^ sender, EventArgs^ e)
		{
			this->Controls->Remove(message);
			timer->Stop();
		}

		//"Ввести из файла"
		void buttonFile_Click(System::Object^ sender, System::EventArgs^ e) {

			//поле под название
			textFile = gcnew TextBox();
			textFile->Location = System::Drawing::Point(this->ClientSize.Width * 0.7, this->ClientSize.Height * 0.42);
			textFile->Size = System::Drawing::Size(this->ClientSize.Width * 0.18, this->ClientSize.Height * 0.05);
			textFile->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", (this->ClientSize.Height * 0.02), System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Controls->Remove(buttonFile);
			this->Controls->Add(textFile);

			//кнопка подтверждения
			butOk->Location = System::Drawing::Point(this->ClientSize.Width * 0.88, this->ClientSize.Height * 0.4175);
			butOk->Size = System::Drawing::Size(this->ClientSize.Width * 0.05, this->ClientSize.Height * 0.049);
			butOk->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", (this->ClientSize.Height * 0.015), System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			butOk->Text = "Ок";
			this->Controls->Add(butOk);
		}
		void butOk_Click(System::Object^ sender, System::EventArgs^ e) {

			polygon->setFirst(nullptr); //обнуление многоугольника

			using namespace Runtime::InteropServices;
			const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(textFile->Text)).ToPointer();
			std::ifstream fin(chars);
			double X, Y;
			if (fin.is_open()) {
				while (!fin.eof()) {
					while (!fin.eof() && !(fin >> X)); //пропустит некорректные символы
					while (!fin.eof() && !(fin >> Y)); //пропустит некорректные символы
					polygon->AddPoint(X, factor * Y); //добавление точки
				}
			}
			this->Controls->Remove(butOk);
			this->Controls->Remove(textFile);
			this->Controls->Add(buttonFile);
		}

		//"Построить многоугольник"
		void buttonDraw_Click(System::Object^ sender, System::EventArgs^ e) {

			Draw(); //очищение формы

			if (polygon->getFirst()) { //существует многоугольник 
				drawFromPoint(polygon->getFirst());
				visible = true; 
				split = false;
			}
			else {
				message->ForeColor = Color::Red;
				message->Text = "Многоугольника ещё нет!";
				this->Controls->Add(message);
				timer->Interval = 3000;
				timer->Start();
			}
		}

		//"Разбить многоугольник"
		void buttonSplitting_Click(System::Object^ sender, System::EventArgs^ e) {

			if (polygon->getFirst()) { //существует многоугольник

				Draw();

				fout = gcnew IO::StreamWriter("output.txt");
				Polygon^ polygonSplit = gcnew Polygon(polygon); //копия многоугольника создается, чтобы не портить исходный
				Polygon::del = gcnew Polygon::Delegate(this, &MyForm::proccesingFirstPoint); //функция, которая будет получать первые точки полученных многоугольников
				Polygon::Splitting(polygonSplit); //разбиение

				fout->Close();

				if (!split) { //если данный многоугольник еще не разбивали, появится вопрос о записи в файл
					MyQuestion^ QuestionForm = gcnew MyQuestion();
					QuestionForm->ShowDialog();

					split = true;
				}
			}
			else {
				message->ForeColor = Color::Red;
				message->Text = "Многоугольника ещё нет!";
				this->Controls->Add(message);
				timer->Interval = 3000;
				timer->Start();
			}
		}

		//функция для рисования многоугольника по первой точке
		void drawFromPoint(MyPoints::Point^ first) {
			if (!streching) forDrawning(); //расчет коэффициентов масштабирования, если их еще нет

			MyPoints::Point^ cur = gcnew MyPoints::Point();
			cur = first;
			do {
				Graphics^ gr = this->CreateGraphics();
				gr->DrawLine(gcnew Pen(Color::PaleVioletRed), (int)((cur->getX() - minX) * streching + shiftX), (int)((cur->getY() - minY) * streching + shiftY),
					(int)((cur->getCurNext()->getX() - minX) * streching + shiftX), (int)((cur->getCurNext()->getY() - minY) * streching + shiftY));
				cur = cur->getCurNext();
			} while (cur != first);
		}
		//расчет коэффициентов масштабирования
		void forDrawning() {
			//для масштабирования изображения многоугольник вписывается в белый прямоугольник на форме
			maxX = polygon->getFirst()->getX();
			minX = polygon->getFirst()->getX();
			maxY = polygon->getFirst()->getY();
			minY = polygon->getFirst()->getY();

			MyPoints::Point^ cur = gcnew MyPoints::Point();
			cur = polygon->getFirst()->getCurNext();
			do {
				if (cur->getCurNext()->getX() > maxX) maxX = cur->getCurNext()->getX();
				else if (cur->getCurNext()->getX() < minX) minX = cur->getCurNext()->getX();
				if (cur->getCurNext()->getY() > maxY) maxY = cur->getCurNext()->getY();
				else if (cur->getCurNext()->getY() < minY) minY = cur->getCurNext()->getY();
				cur = cur->getCurNext();
			} while (cur != polygon->getFirst());

			double stretchingX = 0.58 * this->ClientSize.Width / (maxX - minX); //растяжение по X
			double stretchingY = 0.78 * this->ClientSize.Height / (maxY - minY); //растяжение по Y

			if (stretchingX > stretchingY) streching = stretchingY; else streching = stretchingX;

			//для центровки
			shiftX = 0.06 * this->ClientSize.Width + (0.58 * this->ClientSize.Width - (maxX - minX) * streching) / 2;
			shiftY = 0.06 * this->ClientSize.Height + (0.78 * this->ClientSize.Height - (maxY - minY) * streching) / 2;
		}

		//изменение размера формы
		void SizeChanged(System::Object^ sender, System::EventArgs^ e) {
			if (this->WindowState != FormWindowState::Minimized) { //не относится к сворачиванию формы
				Clean(); //форма очищается
				Draw(); //и отрисовывается заново
				if (split) buttonSplitting_Click(sender, e); //если многоугольник был разбит или построен, рисунок восстанавливается 
				else if (visible) buttonDraw_Click(sender, e);
			}
		}
		//очистка формы
		void Clean() {
			this->Controls->Clear();
			streching = 0; //при изменении размера нужны новые коэффициенты
			Graphics^ gr = this->CreateGraphics(); //убираем поле для рисования
			Brush^ brush = gcnew SolidBrush(this->BackColor);
			gr->FillRectangle(brush, xRect, yRect, widthRect, heightRect);
		}

		//обработка первой точки, полученного при разбиении многоугольника 
		void proccesingFirstPoint(MyPoints::Point^ first) {
			drawFromPoint(first); //отрисовка многоугольника
			if(!split) writeInFile(first, fout); //если многоугольник не разбивали до этого, запись в файл
		}
		//запись координат в файл
		void writeInFile(MyPoints::Point^ first, IO::StreamWriter^ fout) {
			MyPoints::Point^ cur = gcnew MyPoints::Point();
			cur = first;

			do {
				fout->WriteLine(cur->getX() + "  " + factor * cur->getY());
				cur = cur->getCurNext();
			} while (cur != first);
			fout->WriteLine(cur->getX() + "  " + factor * cur->getY());
			fout->WriteLine();
		}

		//функция для вопроса об осях 
		void axeUp(bool Up) {
			if (Up) factor = -1; else factor = 1;
		}

		//"Новый многоугольник"
		void buttonNewPolygon_Click(System::Object^ sender, System::EventArgs^ e) {
			polygon->setFirst(nullptr); //обнуление многоугольника
			split = visible = 0; 
			Clean(); //очистка формы
			Draw(); //отрисовка формы
		}

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->SuspendLayout();
			
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(900, 700);
			this->Text = L"Разбиение невыпуклого многоугольника";
			this->StartPosition = FormStartPosition::CenterScreen;
			this->Name = L"MyForm";
			this->ResumeLayout(false);

			this->Shown += gcnew System::EventHandler(this, &MyForm::Form_Shown);

			buttonAdd = gcnew Button();
			buttonAdd->Click += gcnew System::EventHandler(this, &MyForm::buttonAdd_Click);

			buttonFile = gcnew Button();
			buttonFile->Click += gcnew System::EventHandler(this, &MyForm::buttonFile_Click);

			buttonDraw = gcnew Button();
			buttonDraw->Click += gcnew System::EventHandler(this, &MyForm::buttonDraw_Click);

			buttonSplitting = gcnew Button();
			buttonSplitting->Click += gcnew System::EventHandler(this, &MyForm::buttonSplitting_Click);

			butOk = gcnew Button();
			butOk->Click += gcnew System::EventHandler(this, &MyForm::butOk_Click);

			this->ClientSizeChanged += gcnew System::EventHandler(this, &MyForm::SizeChanged);

			polygon = gcnew Polygon();

			buttonNewPolygon = gcnew Button(); 
			buttonNewPolygon->Click += gcnew System::EventHandler(this, &MyForm::buttonNewPolygon_Click);

			timer = gcnew Timer();
			timer->Enabled = false;
			timer->Tick += gcnew System::EventHandler(this, &MyForm::timer_Tick);
		}
#pragma endregion
	};
}
