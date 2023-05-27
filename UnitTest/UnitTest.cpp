#include "pch.h"
#include "CppUnitTest.h"
#include "..\ЛабораторнРабота6_2\ЛабораторнРабота6_2.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1lab62
{
	TEST_CLASS(UnitTest1lab62)
	{
	public:

		TEST_METHOD(TestProduct)
		{
			// Создание объекта Ingredient
			Product ingredient("Картошка", 77.0, 200.0);

			// Проверка значений полей объекта Ingredient
			Assert::AreEqual(std::string("Картошка"), ingredient.getName());
			Assert::AreEqual(77.0, ingredient.getCaloriesPer100g());
			Assert::AreEqual(200.0, ingredient.getQuantity());
		}
		TEST_METHOD(TestRecipe)
		{
			// Создать объект рецепта
			Recipe recipe;

			// Создайте макет ингредиентов
			Product ingredient1("Картошка", 77.0, 200.0);
			Product ingredient2("Лук", 40.0, 50.0);
			Product ingredient3("Майонез", 625.0, 100.0);

			double calor = (77 * 200 + 40 * 50 + 625 * 100) / 100;
			// Добавьте ингредиенты к рецепту
			recipe.addIngredient(&ingredient1);
			recipe.addIngredient(&ingredient2);
			recipe.addIngredient(&ingredient3);

			//подсчет в функции калорий
			CalorieVisitor calorieVisitor;
			recipe.accept(calorieVisitor);

			// Проверка значений 
			Assert::AreEqual(calor, calorieVisitor.getTotalCalories());

		}
	};
}