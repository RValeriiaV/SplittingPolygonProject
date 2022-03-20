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
	
	//����� � ������������� ����������
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
			this->Text = L"��������� ����������� ��������������";
			this->StartPosition = FormStartPosition::CenterScreen;

			//������ "������"
			buttonStart = gcnew Button();
			buttonStart->Location = System::Drawing::Point(this->ClientSize.Width * 0.4, this->ClientSize.Height * 0.75);
			buttonStart->Size = System::Drawing::Size(this->ClientSize.Width * 0.2, this->ClientSize.Height * 0.15);
			buttonStart->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", (float)(this->ClientSize.Height * 0.05), System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			buttonStart->Text = "������";
			buttonStart->UseVisualStyleBackColor = true;
			buttonStart->TabStop = false; //������� ����� (����� ���������) � ������
			this->Controls->Add(buttonStart);

			//�������������� ���������
			text = gcnew TextBox();
			text->Location = System::Drawing::Point(this->ClientSize.Width * 0.1, this->ClientSize.Height * 0.1);
			text->Size = System::Drawing::Size(this->ClientSize.Width * 0.8, this->ClientSize.Height * 0.7);
			text->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", (float)(this->ClientSize.Height * 0.06), System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			text->Text = "����� ����������!\r\n ����������, ������� ���������� ����� �� ������� �� ������� �������\r\n  \n" +
				"(�������� ��������, ��� ���������� ����� �������� � ����������������� ������� - ����� �������)";
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

	//����� � �������� � ���������� ���������� � ����
	public ref class MyQuestion : public System::Windows::Forms::Form {
	public:
		MyQuestion(void)
		{
			InitializeComponent();
		}

	private:
		Button^ buttonYes; //������ "��"
		Button^ buttonNo; //������ "���"
		TextBox^ questionBox; //����� �������
		TextBox^ filenameBox; //���� ��� ��� �����
		TextBox^ extension; //���������� �����
		Button^ continueBut; //������ "����������"
	protected:
		
		void InitializeComponent(void)
		{
			this->ClientSize = System::Drawing::Size(450, 120);
			this->Text = L"��������� ����������� ��������������";
			this->StartPosition = FormStartPosition::CenterScreen;

			//������ � ����������
			questionBox = gcnew TextBox();
			questionBox->Location = System::Drawing::Point(this->ClientSize.Width * 0.1, this->ClientSize.Height * 0.1);
			questionBox->Size = System::Drawing::Size(this->ClientSize.Width * 0.8, this->ClientSize.Height * 0.5);
			questionBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", (float)(this->ClientSize.Height * 0.1), System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			questionBox->Text = "�� ������ ��������� ���� � ������������ ������ ���������������, ���������� � ���������� ���������?";
			questionBox->Multiline = true;
			questionBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			questionBox->BackColor = this->BackColor;
			questionBox->BorderStyle = BorderStyle::None;
			questionBox->TabStop = false;
			this->Controls->Add(questionBox);

			//������ "��"
			buttonYes = gcnew Button();
			buttonYes->Location = System::Drawing::Point(this->ClientSize.Width * 0.25, this->ClientSize.Height * 0.7);
			buttonYes->Size = System::Drawing::Size(this->ClientSize.Width * 0.2, this->ClientSize.Height * 0.25);
			buttonYes->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", (float)(this->ClientSize.Height * 0.1), System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			buttonYes->Text = "��";
			buttonYes->UseVisualStyleBackColor = true;
			buttonYes->TabStop = false; //������� ����� (����� ���������) � ������
			this->Controls->Add(buttonYes);
			this->buttonYes->Click += gcnew System::EventHandler(this, &MyQuestion::buttonYes_Click);

			//������ "���"
			buttonNo = gcnew Button();
			buttonNo->Location = System::Drawing::Point(this->ClientSize.Width * 0.55, this->ClientSize.Height * 0.7);
			buttonNo->Size = System::Drawing::Size(this->ClientSize.Width * 0.2, this->ClientSize.Height * 0.25);
			buttonNo->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", (float)(this->ClientSize.Height * 0.1), System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			buttonNo->Text = "���";
			buttonNo->UseVisualStyleBackColor = true;
			buttonNo->TabStop = false; //������� ����� (����� ���������) � ������
			this->Controls->Add(buttonNo);
			this->buttonNo->Click += gcnew System::EventHandler(this, &MyQuestion::buttonNo_Click);

			//���� "��� �����"
			filenameBox = gcnew TextBox();
			filenameBox->Location = System::Drawing::Point(this->ClientSize.Width * 0.2, this->ClientSize.Height * 0.3);
			filenameBox->Size = System::Drawing::Size(this->ClientSize.Width * 0.54, this->ClientSize.Height * 0.2);
			filenameBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", (float)(this->ClientSize.Height * 0.1), System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			filenameBox->Multiline = true;
			filenameBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			filenameBox->TabStop = false;

			//����������
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

			//������ "����������"
			continueBut = gcnew Button();
			continueBut->Location = System::Drawing::Point(this->ClientSize.Width * 0.35, this->ClientSize.Height * 0.7);
			continueBut->Size = System::Drawing::Size(this->ClientSize.Width * 0.3, this->ClientSize.Height * 0.25);
			continueBut->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", (float)(this->ClientSize.Height * 0.1), System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			continueBut->Text = "����������";
			continueBut->UseVisualStyleBackColor = true;
			continueBut->TabStop = false; //������� ����� (����� ���������) � ������
			this->continueBut->Click += gcnew System::EventHandler(this, &MyQuestion::continueBut_Click);
		}
		
		void buttonNo_Click(System::Object^ sender, System::EventArgs^ e) {
			remove("output.txt");
			this->Close();
		}

		void buttonYes_Click(System::Object^ sender, System::EventArgs^ e) {

			this->Controls->Remove(buttonNo);
			this->Controls->Remove(buttonYes);
			questionBox->Text = "������� ��� ����� ��� ����������:";
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

	//����� � �������� � ����������� 
	public ref class MyAxes: public System::Windows::Forms::Form
	{
	public:
		MyAxes(void)
		{
			InitializeComponent();
		}

	private:
		TextBox^ questionBox; //������ �� ����
		Button^ buttonUp; //������ "��� �����"
		Button^ buttonDown; //������ "��� ����"
		bool* thisUp; //������, ���� ��� �����

	protected:
		void InitializeComponent(void) {

			this->ClientSize = System::Drawing::Size(504, 400);
			this->Text = L"��������� ����������� ��������������";
			this->StartPosition = FormStartPosition::CenterScreen;

			//������ � ����������� ����
			questionBox = gcnew TextBox();
			questionBox->Location = System::Drawing::Point(this->ClientSize.Width * 0.1, this->ClientSize.Height * 0.05);
			questionBox->Size = System::Drawing::Size(this->ClientSize.Width * 0.8, this->ClientSize.Height * 0.1);
			questionBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", (float)(this->ClientSize.Height * 0.05), System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			questionBox->Text = "��� ��������� ���?";
			questionBox->Multiline = true;
			questionBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			questionBox->BackColor = this->BackColor;
			questionBox->BorderStyle = BorderStyle::None;
			questionBox->TabStop = false;
			this->Controls->Add(questionBox);


			Resources::ResourceManager^ rm = gcnew Resources::ResourceManager("SplittingPolygonProject.Resources", Reflection::Assembly::GetExecutingAssembly());

			//������ "��� �����"
			buttonUp = gcnew Button();
			buttonUp->Location = System::Drawing::Point(this->ClientSize.Width * 0.1, this->ClientSize.Height * 0.2);
			buttonUp->Size = System::Drawing::Size(this->ClientSize.Width * 0.35, this->ClientSize.Height * 0.7);
			buttonUp->BackgroundImage = safe_cast<System::Drawing::Bitmap^>(rm->GetObject("pictureUp"));
			buttonUp->BackgroundImageLayout = ImageLayout::Zoom;
			buttonUp->TabStop = false;
			this->Controls->Add(buttonUp);
			this->buttonUp->Click += gcnew System::EventHandler(this, &MyAxes::buttonUp_Click);

			//������ "��� ����"
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

	//�������� �����
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:

		MyForm(void)
		{
			InitializeComponent();
			Message(); //����� �������������� ���������
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
		TextBox^ numberX; //���� ��� ���������� X
		TextBox^ numberY; //���� ��� ���������� Y

		Polygon^ polygon; //�������������

		Button^ buttonAdd; //������ "�������� �����"
		TextBox^ message; //��������� � ������������ �����
		Timer^ timer; //������, �� �������� ��������� ��������

		Button^ buttonFile; //������ "������ �� �����"
		TextBox^ textFile; //��� �������� �����
		Button^ butOk; //������������� ����� �� �����

		Button^ buttonDraw; //������ "��������� �������������"
		Button^ buttonSplitting; //������ "������� �������������"

		Button^ buttonNewPolygon; //������ "����� �������������"

		//��� ��������������� ����������� ��������������
		double streching = 0; //���������� �� ����
		int shiftX; //����� �� X ��� ���������
		int shiftY; //����� �� Y ��� ���������
		double maxX; //��� ������� ���������� ��������
		double minX;
		double maxY;
		double minY;

		char factor = -1; //��� ��� ������ ������� � ���� OY ����, ���� ������������ ������ "�����" ���������� �� Y ����������� �� -1, ��� ������������� ������������ ����� ����� ���������

		//��������� ���� ��� ���������
		int xRect;
		int yRect;
		int widthRect;
		int heightRect;

		//����� ��� ��������� �������� ����� ��� ���������� ���������
		bool visible; //������������� ��������
		bool split; //������������� ������

		IO::StreamWriter^ fout; //����� ���������� � ����

	protected:

		//����� ��������� - ��������� �����, ������ �� ����
		void Form_Shown(System::Object^ sender, System::EventArgs^ e) {
			Draw();
			MyAxes^ axeBox = gcnew MyAxes();
			axeBox->del = gcnew MyAxes::Delegate(this, &MyForm::axeUp);
			axeBox->ShowDialog();
		}

		//����� ����� ��������������� ���������
		void Message() { //����� ����� � �������������� ����������
			MyMessageBox^ msgBox = gcnew MyMessageBox();
			msgBox->ShowDialog();
		}

		//��������� �������� �����
		void Draw() { //��������� ������ � ����� �����

			int left = this->ClientSize.Width * 0.7; //����� ���������� ����������� ��������

			int sizeOfText; //������ ������ �� ���������
			if ((this->ClientSize.Height * 0.02) < (this->ClientSize.Width * 0.016)) sizeOfText = (this->ClientSize.Height * 0.02);
			else sizeOfText = (this->ClientSize.Width * 0.016);

			//���� � ������� X=
			TextBox^ textX = gcnew TextBox();
			textX->Location = System::Drawing::Point(left, this->ClientSize.Height * 0.205);
			textX->Size = System::Drawing::Size(this->ClientSize.Width * 0.03, this->ClientSize.Height * 0.05);
			textX->TextAlign = HorizontalAlignment::Right;
			textX->Text = "X =";
			textX->BackColor = this->BackColor;
			textX->BorderStyle = BorderStyle::None;
			textX->TabStop = false;
			this->Controls->Add(textX);

			//���� � ������� Y=
			TextBox^ textY = gcnew TextBox();
			textY->Location = System::Drawing::Point(left, this->ClientSize.Height * 0.255);
			textY->Size = System::Drawing::Size(this->ClientSize.Width * 0.03, this->ClientSize.Height * 0.05);
			textY->TextAlign = HorizontalAlignment::Right;
			textY->Text = "Y =";
			textY->BackColor = this->BackColor;
			textY->BorderStyle = BorderStyle::None;
			textY->TabStop = false;
			this->Controls->Add(textY);

			//������ "������ �� �����"
			buttonFile->Location = System::Drawing::Point(left, this->ClientSize.Height * 0.42);
			buttonFile->Size = System::Drawing::Size(this->ClientSize.Width * 0.23, this->ClientSize.Height * 0.055);
			buttonFile->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", sizeOfText, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			buttonFile->Text = "������ �� �����";
			buttonFile->TabStop = false;
			this->Controls->Add(buttonFile);

			//������ "��������� �������������"
			buttonDraw->Location = System::Drawing::Point(left, this->ClientSize.Height * 0.55);
			buttonDraw->Size = System::Drawing::Size(this->ClientSize.Width * 0.23, this->ClientSize.Height * 0.1);
			buttonDraw->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", sizeOfText, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			buttonDraw->Text = "���������\n �������������";
			buttonDraw->TabStop = false;
			this->Controls->Add(buttonDraw);

			//������ "������� �������������"
			buttonSplitting->Location = System::Drawing::Point(left, this->ClientSize.Height * 0.7);
			buttonSplitting->Size = System::Drawing::Size(this->ClientSize.Width * 0.23, this->ClientSize.Height * 0.1);
			buttonSplitting->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", sizeOfText, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			buttonSplitting->Text = "�������\n �������������";
			buttonSplitting->TabStop = false;
			this->Controls->Add(buttonSplitting);

			//���������
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

			//���� ��� ����� ������ X
			numberX = gcnew TextBox();
			numberX->Location = System::Drawing::Point(left, this->ClientSize.Height * 0.2);
			numberX->Size = System::Drawing::Size(this->ClientSize.Width * 0.15, this->ClientSize.Height * 0.05);
			textX->TabStop = false;
			this->Controls->Add(numberX);

			//���� ��� ����� ������ Y
			numberY = gcnew TextBox();
			numberY->Location = System::Drawing::Point(left, this->ClientSize.Height * 0.25);
			numberY->Size = System::Drawing::Size(this->ClientSize.Width * 0.15, this->ClientSize.Height * 0.05);
			textX->TabStop = false;
			this->Controls->Add(numberY);

			//������ "�������� �����"
			buttonAdd->Location = System::Drawing::Point(left, this->ClientSize.Height * 0.3);
			buttonAdd->Size = System::Drawing::Size(this->ClientSize.Width * 0.15, this->ClientSize.Height * 0.1);
			buttonAdd->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", sizeOfText, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			buttonAdd->Text = "��������\n �����";
			this->Controls->Add(buttonAdd);

			buttonNewPolygon->Location = System::Drawing::Point(this->ClientSize.Width * 0.4, this->ClientSize.Height * 0.88);
			buttonNewPolygon->Size = System::Drawing::Size(this->ClientSize.Width * 0.2, this->ClientSize.Height * 0.1);
			buttonNewPolygon->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", sizeOfText, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			buttonNewPolygon->Text = "����� �������������";
			this->Controls->Add(buttonNewPolygon);

			//������� ��� ���������
			Graphics^ gr = this->CreateGraphics();
			xRect = 0.05 * this->ClientSize.Width;
			yRect = 0.05 * this->ClientSize.Height;
			widthRect = 0.6 * this->ClientSize.Width;
			heightRect = 0.8 * this->ClientSize.Height;
			Brush^ brush = gcnew SolidBrush(Color::White);
			gr->FillRectangle(brush, xRect, yRect, widthRect, heightRect);
		}

		//"�������� �����"
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
				message->Text = "������������ ����!"; //��������������� ���������
				this->Controls->Add(message);
				timer->Interval = 2000;
				timer->Start();
			}

			if (!error) { //���� ������ ������� ���������
				polygon->AddPoint(X, factor * Y); //��������� � ������������� � ������ ����������� ���
				if (Controls->Contains(message)) { //���� �� ����� ���� ������
					message->ForeColor = Color::Green;
					message->Text = "������� :)";
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

		//"������ �� �����"
		void buttonFile_Click(System::Object^ sender, System::EventArgs^ e) {

			//���� ��� ��������
			textFile = gcnew TextBox();
			textFile->Location = System::Drawing::Point(this->ClientSize.Width * 0.7, this->ClientSize.Height * 0.42);
			textFile->Size = System::Drawing::Size(this->ClientSize.Width * 0.18, this->ClientSize.Height * 0.05);
			textFile->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", (this->ClientSize.Height * 0.02), System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Controls->Remove(buttonFile);
			this->Controls->Add(textFile);

			//������ �������������
			butOk->Location = System::Drawing::Point(this->ClientSize.Width * 0.88, this->ClientSize.Height * 0.4175);
			butOk->Size = System::Drawing::Size(this->ClientSize.Width * 0.05, this->ClientSize.Height * 0.049);
			butOk->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", (this->ClientSize.Height * 0.015), System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			butOk->Text = "��";
			this->Controls->Add(butOk);
		}
		void butOk_Click(System::Object^ sender, System::EventArgs^ e) {

			polygon->setFirst(nullptr); //��������� ��������������

			using namespace Runtime::InteropServices;
			const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(textFile->Text)).ToPointer();
			std::ifstream fin(chars);
			double X, Y;
			if (fin.is_open()) {
				while (!fin.eof()) {
					while (!fin.eof() && !(fin >> X)); //��������� ������������ �������
					while (!fin.eof() && !(fin >> Y)); //��������� ������������ �������
					polygon->AddPoint(X, factor * Y); //���������� �����
				}
			}
			this->Controls->Remove(butOk);
			this->Controls->Remove(textFile);
			this->Controls->Add(buttonFile);
		}

		//"��������� �������������"
		void buttonDraw_Click(System::Object^ sender, System::EventArgs^ e) {

			Draw(); //�������� �����

			if (polygon->getFirst()) { //���������� ������������� 
				drawFromPoint(polygon->getFirst());
				visible = true; 
				split = false;
			}
			else {
				message->ForeColor = Color::Red;
				message->Text = "�������������� ��� ���!";
				this->Controls->Add(message);
				timer->Interval = 3000;
				timer->Start();
			}
		}

		//"������� �������������"
		void buttonSplitting_Click(System::Object^ sender, System::EventArgs^ e) {

			if (polygon->getFirst()) { //���������� �������������

				Draw();

				fout = gcnew IO::StreamWriter("output.txt");
				Polygon^ polygonSplit = gcnew Polygon(polygon); //����� �������������� ���������, ����� �� ������� ��������
				Polygon::del = gcnew Polygon::Delegate(this, &MyForm::proccesingFirstPoint); //�������, ������� ����� �������� ������ ����� ���������� ���������������
				Polygon::Splitting(polygonSplit); //���������

				fout->Close();

				if (!split) { //���� ������ ������������� ��� �� ���������, �������� ������ � ������ � ����
					MyQuestion^ QuestionForm = gcnew MyQuestion();
					QuestionForm->ShowDialog();

					split = true;
				}
			}
			else {
				message->ForeColor = Color::Red;
				message->Text = "�������������� ��� ���!";
				this->Controls->Add(message);
				timer->Interval = 3000;
				timer->Start();
			}
		}

		//������� ��� ��������� �������������� �� ������ �����
		void drawFromPoint(MyPoints::Point^ first) {
			if (!streching) forDrawning(); //������ ������������� ���������������, ���� �� ��� ���

			MyPoints::Point^ cur = gcnew MyPoints::Point();
			cur = first;
			do {
				Graphics^ gr = this->CreateGraphics();
				gr->DrawLine(gcnew Pen(Color::PaleVioletRed), (int)((cur->getX() - minX) * streching + shiftX), (int)((cur->getY() - minY) * streching + shiftY),
					(int)((cur->getCurNext()->getX() - minX) * streching + shiftX), (int)((cur->getCurNext()->getY() - minY) * streching + shiftY));
				cur = cur->getCurNext();
			} while (cur != first);
		}
		//������ ������������� ���������������
		void forDrawning() {
			//��� ��������������� ����������� ������������� ����������� � ����� ������������� �� �����
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

			double stretchingX = 0.58 * this->ClientSize.Width / (maxX - minX); //���������� �� X
			double stretchingY = 0.78 * this->ClientSize.Height / (maxY - minY); //���������� �� Y

			if (stretchingX > stretchingY) streching = stretchingY; else streching = stretchingX;

			//��� ���������
			shiftX = 0.06 * this->ClientSize.Width + (0.58 * this->ClientSize.Width - (maxX - minX) * streching) / 2;
			shiftY = 0.06 * this->ClientSize.Height + (0.78 * this->ClientSize.Height - (maxY - minY) * streching) / 2;
		}

		//��������� ������� �����
		void SizeChanged(System::Object^ sender, System::EventArgs^ e) {
			if (this->WindowState != FormWindowState::Minimized) { //�� ��������� � ������������ �����
				Clean(); //����� ���������
				Draw(); //� �������������� ������
				if (split) buttonSplitting_Click(sender, e); //���� ������������� ��� ������ ��� ��������, ������� ����������������� 
				else if (visible) buttonDraw_Click(sender, e);
			}
		}
		//������� �����
		void Clean() {
			this->Controls->Clear();
			streching = 0; //��� ��������� ������� ����� ����� ������������
			Graphics^ gr = this->CreateGraphics(); //������� ���� ��� ���������
			Brush^ brush = gcnew SolidBrush(this->BackColor);
			gr->FillRectangle(brush, xRect, yRect, widthRect, heightRect);
		}

		//��������� ������ �����, ����������� ��� ��������� �������������� 
		void proccesingFirstPoint(MyPoints::Point^ first) {
			drawFromPoint(first); //��������� ��������������
			if(!split) writeInFile(first, fout); //���� ������������� �� ��������� �� �����, ������ � ����
		}
		//������ ��������� � ����
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

		//������� ��� ������� �� ���� 
		void axeUp(bool Up) {
			if (Up) factor = -1; else factor = 1;
		}

		//"����� �������������"
		void buttonNewPolygon_Click(System::Object^ sender, System::EventArgs^ e) {
			polygon->setFirst(nullptr); //��������� ��������������
			split = visible = 0; 
			Clean(); //������� �����
			Draw(); //��������� �����
		}

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->SuspendLayout();
			
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(900, 700);
			this->Text = L"��������� ����������� ��������������";
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
