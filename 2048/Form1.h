#pragma once


namespace My2048 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}
		//按下键盘方向键上
		void kup(){
			int temp, r;
			int row, col;
			for(col = 0; col < 4; col++)
			{
				temp = r = 0;
				for (row = 0; row < 4; row++)
				{
					if(weizhi[row,col] == 0)
						continue;
					if(weizhi[row,col] == temp){
						weizhi[r,col] = 2*temp;
						weizhi[row,col] = 0;
						temp = 0;
						r++;
					}
					else if(temp != 0){
						weizhi[r,col] = temp;
						temp = weizhi[row,col];
						weizhi[row,col] = 0;
						r++;
					}
					else
					{
						temp = weizhi[row,col];
						weizhi[row,col] = 0;
					}
				}
				if(temp != 0)
					weizhi[r,col] = temp;
			}

		}
				
		//按下键盘方向键下
		void kdown(){
			int temp, r;
			int row, col;
			for(col = 0; col < 4; col++)
			{
				temp = 0;
				r = 3;
				for (row = 3; row >= 0; row--)
				{
					if(weizhi[row,col] == 0)
						continue;
					if(weizhi[row,col] == temp){
						weizhi[r,col] = 2*temp;
						weizhi[row,col] = 0;
						temp = 0;
						r--;
					}
					else if(temp != 0){
						weizhi[r,col] = temp;
						temp = weizhi[row,col];
						weizhi[row,col] = 0;
						r--;
					}
					else
					{
						temp = weizhi[row,col];
						weizhi[row,col] = 0;
					}
				}
				if(temp != 0)
					weizhi[r,col] = temp;
			}

		}
		//按下键盘方向键左
		void kleft(){
			int temp, cl;
			int row, col;
			for(row = 0; row < 4; row++)
			{
				temp = cl = 0;
				for (col = 0; col < 4; col++)
				{
					if(weizhi[row,col] == 0)
						continue;
					if(weizhi[row,col] == temp){
						weizhi[row,cl] = 2*temp;
						weizhi[row,col] = 0;
						temp = 0;
						cl++;
					}
					else if(temp != 0){
						weizhi[row,cl] = temp;
						temp = weizhi[row,col];
						weizhi[row,col] = 0;
						cl++;
					}
					else
					{
						temp = weizhi[row,col];
						weizhi[row,col] = 0;
					}
				}
				if(temp != 0)
					weizhi[row,cl] = temp;
			}

		}
		//按下键盘方向键右
		void kright(){
			int temp, cl;
			int row, col;
			for(row = 0; row < 4; row++)
			{
				temp = 0;
				cl = 3;
				for (col = 3; col >= 0; col--)
				{
					if(weizhi[row,col] == 0)
						continue;
					if(weizhi[row,col] == temp){
						weizhi[row,cl] = 2*temp;
						weizhi[row,col] = 0;
						temp = 0;
						cl--;
					}
					else if(temp != 0){
						weizhi[row,cl] = temp;
						temp = weizhi[row,col];
						weizhi[row,col] = 0;
						cl--;
					}
					else
					{
						temp = weizhi[row,col];
						weizhi[row,col] = 0;
					}
				}
				if(temp != 0)
					weizhi[row,cl] = temp;
			}
		}
		//添加随机值
		bool addshuzi(){
			int u, v;
			//探测空的位置
			int row[7] = {0, +1, -1, +2, -2, +3, -3};
			int col[7] = {0, +1, -1, +2, -2, +3, -3};
			//产生的随机位置（i,j）
			int i = (Convert::ToInt32(random->NextDouble()*16)) % 4;
			int j = (Convert::ToInt32(random->NextDouble()*16)) % 4;
			//产生的随机数2/4
			int k = (Convert::ToInt32(random->NextDouble()*16)) % 4;
			if (k == 0)
				k = 2;
			else
				k = 4;
			String ^str = String::Format(L"image/{0}.png", k);
			if (weizhi[i,j] != 0)
			{	for (int r = 0; r < 7; r++)
				{
					u = i+row[r];
					if( u >= 0 && u < 4){
						for (int c = 0; c < 7; c++)
						{
							v = j+col[c];
							if( v >= 0 && v < 4 && weizhi[u,v] == 0)
							{
								shuzi[u,v]->BackgroundImage = Image::FromFile(str);
								shuzi[u,v]->Visible = true;
								weizhi[u,v] = k;
								return true;
							}			
						}
					}
				}				
			}
			else{
				shuzi[i,j]->BackgroundImage = Image::FromFile(str);
				shuzi[i,j]->Visible = true;
				weizhi[i,j] = k;
				return true;
			}
			return false;
		}
		//更新背景
		void changeBg(){
			for (int i = 0; i < 4; i++)
			 for (int j = 0; j < 4; j++)
			 {
				 if(weizhi[i,j] != 0){
					 String ^str = String::Format(L"Image/{0}.png",weizhi[i,j]);
					 shuzi[i,j]->BackgroundImage = Image::FromFile(str);
					 shuzi[i,j]->Visible = true;
				 }
				 else
					 shuzi[i,j]->Visible = false;
			 }
		}
		//判定是否结束
		bool gameover(){
			for(int row = 0; row < 3; row++)
				for (int col = 0; col < 4; col++)
				{
					if(weizhi[row,col] == weizhi[row+1,col])
						return false;
				}
			for(int row = 0; row < 4; row++)
				for (int col = 0; col < 3; col++)
				{
					if(weizhi[row,col] == weizhi[row,col+1])
						return false;
				}
				return true;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		Random ^random;
		array<int, 2> ^weizhi;
		array<System::Windows::Forms::PictureBox^, 2> ^shuzi;
		System::ComponentModel::Container		  ^components;
		System::Windows::Forms::Panel			  ^panel1;
		System::Windows::Forms::MenuStrip		  ^menuStrip1;
		System::Windows::Forms::ToolStripMenuItem ^starToolStripMenuTtem;
		bool badd;


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->starToolStripMenuTtem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// panel1
			// 
			this->panel1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->panel1->Location = System::Drawing::Point(1, 127);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(334, 334);
			this->panel1->TabIndex = 0;
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->starToolStripMenuTtem});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(334, 25);
			this->menuStrip1->TabIndex = 2;
			this->menuStrip1->Text = L"重新开始";
			// 
			// starToolStripMenuTtem
			// 
			this->starToolStripMenuTtem->Name = L"starToolStripMenuTtem";
			this->starToolStripMenuTtem->Size = System::Drawing::Size(68, 21);
			this->starToolStripMenuTtem->Text = L"重新开始";
			this->starToolStripMenuTtem->Click += gcnew System::EventHandler(this, &Form1::starToolStripMenuTtem_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(334, 462);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(350, 500);
			this->MinimumSize = System::Drawing::Size(350, 500);
			this->Name = L"Form1";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"2048";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::Form1_Paint);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::Form1_KeyDown);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		static int x, y;
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
				 this->weizhi = (gcnew array<int, 2>(4, 4));
				 this->shuzi  = (gcnew array<System::Windows::Forms::PictureBox^, 2>(4, 4));
				 for (int i = 0; i < 4; i++)
					 for (int j = 0; j < 4; j++)
					 {
						 this->weizhi[i,j] = 0;
						 this->shuzi[i,j] = (gcnew System::Windows::Forms::PictureBox());
					 }
				for (int i = 0; i < 4; i++)
					for (int j = 0; j < 4; j++)
					{
						this->shuzi[i,j]->Name =  L"picturebox1";
						this->shuzi[i,j]->Size = System::Drawing::Size(71, 71);
						this->shuzi[i,j]->TabIndex = 0;
						this->shuzi[i,j]->TabStop = false;
						this->shuzi[i,j]->BringToFront();
						this->shuzi[i,j]->Location=System::Drawing::Point(11+81*j,138+81*i);
						this->Controls->Add(shuzi[i,j]);
						this->shuzi[i,j]->Visible = false;
					}
				random = gcnew Random();
				x = (Convert::ToInt32(random->NextDouble()*16)) % 4;
				y = (Convert::ToInt32(random->NextDouble()*16)) % 4;
				weizhi[x,y] = 2;
				shuzi[x,y]->BackgroundImage=Image::FromFile(L"image/2.png");
				shuzi[x,y]->Visible = true;
				badd = true;
			 }
	private: System::Void Form1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
				 switch(e->KeyData){
					 //键盘上键
					 case System::Windows::Forms::Keys::Up:
						 //移动合并
						 kup();
						 //背景设置
						 changeBg();
						 //添加新数字
						 badd = addshuzi();
						 //刷新
						 Invalidate();
						 break;
					//键盘下键
					 case System::Windows::Forms::Keys::Down:
						 kdown();
						 changeBg();
						 badd = addshuzi();
						 Invalidate();
						 break;
					 //键盘左键
					 case System::Windows::Forms::Keys::Left:
						 kleft();
						 changeBg();
						 badd = addshuzi();
						 Invalidate();
						 break;
					 //键盘右键
					 case System::Windows::Forms::Keys::Right:
						 kright();
						 changeBg();
						 badd = addshuzi();
						 Invalidate();
						 break;	
					 default: break;
				 }
				 if(!badd && gameover())
					 MessageBox::Show("你跪了笨蛋！！！");
			 }
	private: System::Void Form1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
			 }
	private: System::Void starToolStripMenuTtem_Click(System::Object^  sender, System::EventArgs^  e) {
				 this->Controls->Clear();
				 Form1_Load(sender,e);
				 this->Controls->Add(this->MainMenuStrip);
				 Invalidate();
			 }
	};
}

