#include <Moon.h>

/*
	-----------------
	| Directions :- |
	| 1 - Up        |
	| 2 - Right     |
	| 3 - Down      |
	| 4 - Left      |
	-----------------
*/
class Snake
{
public:
	Snake(Int row, Int col, Int length = 3, Int direction = 2) : m_Row(row), m_Col(col), m_Length(length), m_Direction(direction)
	{
	}

	Int Update()
	{
		if (m_Direction == 1) m_Col++;
		if (m_Direction == 2) m_Row++;
		if (m_Direction == 3) m_Col--;
		if (m_Direction == 4) m_Row--;
		m_Body.insert(m_Body.begin(), Vec2(m_Row, m_Col));
		if (m_Body.size() > m_Length) m_Body.pop_back();
		if (m_Row < 0 || m_Col < 0 || m_Row > 30 || m_Col > 30)
			return -1;
		else
			return 0;
	}

	void SetDirection(Int direction)
	{
		m_Direction = direction;
	}

	inline List<Vec2> GetBody() const { return m_Body; };
private:
	Int m_Row;
	Int m_Col;
	Int m_Length;
	Int m_Direction;
	List<Vec2> m_Body;
}; 

class Grid
{
public:
	Grid(Snake* snake) : m_Snake(snake)
	{
		for (int i = 0; i < 30; i++)
		{
			List<Uint> row;
			for (int j = 0; j < 30; j++)
			{
				row.push_back(0);
			}
			m_Grid.push_back(row);
		}
	}

	void OnUpdate()
	{
		for (Vec2& tail : m_Snake->GetBody())
		{
			m_Grid[(Uint)tail.x][(Uint)tail.y] = 1;
		}
	}

	inline List<List<Uint>> GetGrid() const { return m_Grid; }

	inline static Int GetWidth() { return s_Width; }
	inline static Int GetHeight() { return s_Height; }
private:
	List<List<Uint>> m_Grid;
	Snake* m_Snake;
	static const Int s_Width = 30;
	static const Int s_Height = 30;
};

class Food
{
public:
	Food(Grid* grid) : m_Grid(grid)
	{
		GenerateNew();
	}

	void GenerateNew()
	{
		m_Position = RandomBox(m_Grid);
	}

	static Vec2 RandomBox(Grid* grid)
	{
		Vec2 res(0, 0);
		do
		{
			res.x = (Float)Moon::Util::Random(0, Grid::GetWidth());
			res.y = (Float)Moon::Util::Random(0, Grid::GetHeight());
		} while (grid->GetGrid()[(Int)res.x][(Int)res.y] != 0);
		return res;
	}

	inline Vec2 GetPosition() const { return m_Position; }
private:
	Grid* m_Grid;
	Vec2 m_Position;
};

class Sandbox : public Moon::Application
{
public:
	Sandbox() : snake(nullptr), grid(nullptr), food(nullptr), model(nullptr), black(nullptr), red(nullptr), green(nullptr), score(0)
	{
		Moon::Window::SetDimensions(600, 600);
		Moon::Window::SetTitle("Snake");
	}
	
	void OnStart()
	{
		snake = new Snake(5, 5);
		grid = new Grid(snake);
		food = new Food(grid);

		Int width = 600 / Grid::GetWidth();
		Int height = 600 / Grid::GetHeight();

		black = new Moon::Material(Moon::MaterialType::Color, new Moon::Color(0.0f, 0.0f, 0.0f, 1.0f));
		green = new Moon::Material(Moon::MaterialType::Color, new Moon::Color(0.0f, 255.0f, 0.0f, 1.0f));
		red = new Moon::Material(Moon::MaterialType::Color, new Moon::Color(255.0f, 0.0f, 0.0f, 1.0f));

		model = Moon::Models::Rect(black, 20, 20);
		model->GetShader()->SetProjection(Moon::Math::Ortho(0.f, 600.0f, 0.f, 600.0f, -1.0f, 1.0f));

		Moon::Text* text = new Moon::Text(50, 50, "Score", "arial", 50);
		Moon::Renderer::AddText(text);

		for (Int i = 0; i < Grid::GetWidth(); i++)
		{
			for (Int j = 0; j < Grid::GetHeight(); j++)
			{
				Int x = width * i + 10;
				Int y = height * j + 10;
				Moon::Entity* entity = new Moon::Entity(model, Vec3(x, y, 0));
				entities[entity] = Vec2(i, j);
				Moon::Renderer::AddEntity(entity);
			}
		}

		Moon::CustomEvent* tick = new Moon::CustomEvent(Sandbox::OnCustomUpdate, 100, this);
		Moon::EventHandler::Push(tick);
	}

	static void OnCustomUpdate(void* sb)
	{
		Sandbox* sandbox = (Sandbox*)sb;
		Snake* snake = sandbox->snake;
		
		if (snake->Update() == -1)
		{
			sandbox->Close();
		}

		Vec2 head = snake->GetBody()[0];
		Vec2 foodPosition = sandbox->food->GetPosition();

		if (head.x == foodPosition.x && head.y == foodPosition.y)
		{
			sandbox->food->GenerateNew();
			sandbox->score++;
		}
		
		for (auto& pair : sandbox->entities)
		{
			Moon::Entity* entity = pair.first;
			Vec2 position = pair.second;
			Moon::Material* material = sandbox->black;
			if (position.x == foodPosition.x && position.y == foodPosition.y)
			{
				material = sandbox->red;
			}
			for (const Vec2& tail : snake->GetBody())
			{
				if (tail.x == position.x && tail.y == position.y)
				{
					material = sandbox->green;
				}
			}
			entity->SetMaterial(material);
		}
	}

	void OnUpdate()
	{
		if (Moon::EventHandler::KeyDown("w"))
		{
			snake->SetDirection(1);
		}
		if (Moon::EventHandler::KeyDown("d"))
		{
			snake->SetDirection(2);
		}
		if (Moon::EventHandler::KeyDown("s"))
		{
			snake->SetDirection(3);
		}
		if (Moon::EventHandler::KeyDown("a"))
		{
			snake->SetDirection(4);
		}
	}
private:
	Uint score;
	Snake* snake;
	Food* food;
	Grid* grid;
	Moon::Model* model;
	Moon::Material* black;
	Moon::Material* green;
	Moon::Material* red;
	HashMap<Moon::Entity*, Vec2> entities;
};

Moon::Application* Moon::CreateApplication()
{
	return new Sandbox();
}

