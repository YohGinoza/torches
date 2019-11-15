
class Item
{
public:
	Item();
	~Item();
	virtual void OnRead() = 0;
};

class Healer :
	public Item
{
public:
	Healer();
	~Healer();
	virtual void OnRead() override;
};

class Lighter :
	public Item
{
public:
	Lighter();
	~Lighter();
	virtual void OnRead() override;
};
