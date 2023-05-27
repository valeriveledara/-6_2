#include <iostream>
#include <vector>

// Абстрактный базовый класс Ингредиент
class Ingredient {
public:
    virtual std::string getName() const = 0;
    virtual double getCaloriesPer100g() const = 0;
    virtual double getQuantity() const = 0;
    virtual void accept(class Visitor& visitor) = 0;
};

// Конкретный класс Продукт
class Product : public Ingredient {
private:
    std::string name;
    double caloriesPer100g;
    double quantity;

public:
    Product(const std::string& name, double caloriesPer100g, double quantity)
        : name(name), caloriesPer100g(caloriesPer100g), quantity(quantity) {}

    std::string getName() const override {
        return name;
    }

    double getCaloriesPer100g() const override {
        return caloriesPer100g;
    }

    double getQuantity() const override {
        return quantity;
    }

    void accept(Visitor& visitor) override;
};

// Класс Рецепт блюда
class Recipe {
private:
    std::vector<Ingredient*> ingredients;

public:
    void addIngredient(Ingredient* ingredient) {
        ingredients.push_back(ingredient);
    }

    void accept(Visitor& visitor) {
        for (Ingredient* ingredient : ingredients) {
            ingredient->accept(visitor);
        }
    }
};

// Абстрактный базовый класс Посетитель
class Visitor {
public:
    virtual void visit(Product& product) = 0;
};

// Конкретный класс Посетитель для вывода состава ингредиентов рецепта
class CompositionVisitor : public Visitor {
public:
    void visit(Product& product) override {
        std::cout << product.getQuantity() << " г " << product.getName() << std::endl;
    }
};

// Конкретный класс Посетитель для подсчета калорийности блюда
class CalorieVisitor : public Visitor {
private:
    double totalCalories;

public:
    CalorieVisitor() : totalCalories(0.0) {}

    void visit(Product& product) override {
        double calories = (product.getCaloriesPer100g() * product.getQuantity()) / 100.0;
        totalCalories += calories;
    }

    double getTotalCalories() const {
        return totalCalories;
    }
};

void Product::accept(Visitor& visitor) {
    visitor.visit(*this);
}

int main() {
    setlocale(LC_ALL, "Russian");
    // Создаем продукты (ингредиенты)
    Product potato("Картошка", 77.0, 200.0);
    Product beet("Свекла", 43.0, 150.0);
    Product onion("Лук", 40.0, 50.0);
    Product mayonnaise("Майонез", 625.0, 100.0);
    Product fish("Рыба", 120.0, 300.0);
    Product carrot("Морковь", 40.0, 30.0);

    // Создаем рецепт блюда и добавляем ингредиенты
    Recipe recipe;
    recipe.addIngredient(&potato);
    recipe.addIngredient(&beet);
    recipe.addIngredient(&onion);
    recipe.addIngredient(&mayonnaise);
    recipe.addIngredient(&fish);
    recipe.addIngredient(&carrot);

    // Посетитель для вывода состава ингредиентов рецепта
    CompositionVisitor compositionVisitor;
    recipe.accept(compositionVisitor);

    std::cout << "Калорийность блюда: ";

    // Посетитель для подсчета калорийности блюда
    CalorieVisitor calorieVisitor;
    recipe.accept(calorieVisitor);

    std::cout << calorieVisitor.getTotalCalories() << " ккал" << std::endl;

    return 0;
}