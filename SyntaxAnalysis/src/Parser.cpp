
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

  enum class LexerTokenType {
      PlusToken,
      MinusToken,
      MultiplyToken,
      DivideToken,
      AssignToken,
      VarToken,
      FloatToken,
      IntToken,
      ParenOpen,
      ParenClose,
      PrintToken
  };

struct LexerToken
{
    LexerTokenType type;
    std::string location;
    // Add any other necessary fields
};

struct Node
{
    LexerToken type;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
    // Add other necessary fields
};

class Parser
{
  private:
    std::vector<LexerToken> token;
    size_t current;
    std::vector<std::shared_ptr<Node>> compound;
    std::shared_ptr<Node> root;

    std::shared_ptr<Node> makeNode(std::shared_ptr<Node> &left, std::shared_ptr<Node> &right, LexerToken &type)
    {
        auto node = std::make_shared<Node>();
        node->type = type;
        node->left = left;
        node->right = right;
        return node;
    }

    std::shared_ptr<Node> Assign(std::shared_ptr<Node> &left)
    {
        LexerToken type = token[current];
        current++;

        std::shared_ptr<Node> right = Expression();

        return makeNode(left, right, type);
    }

    std::shared_ptr<Node> Expression()
    {
        std::shared_ptr<Node> left = Term();

        while (current < token.size())
        {
            if (token[current].type == LexerTokenType::PlusToken || token[current].type == LexerTokenType::MinusToken)
            {
                LexerToken type = token[current];
                current++;

                std::shared_ptr<Node> right = Term();
                left = makeNode(left, right, type);
            } else
            {
                break;
            }
        }

        return left;
    }

    std::shared_ptr<Node> Term()
    {
        std::shared_ptr<Node> left = Factor();

        while (current < token.size())
        {
            if (token[current].type == LexerTokenType::MultiplyToken
                || token[current].type == LexerTokenType::DivideToken)
            {
                LexerToken type = token[current];
                current++;

                std::shared_ptr<Node> right = Factor();
                left = makeNode(left, right, type);
            } else
            {
                break;
            }
        }

        return left;
    }

    std::shared_ptr<Node> Factor()
    {
        std::shared_ptr<Node> node = std::make_shared<Node>();

        if (current >= token.size()) { return node; }

        if (token[current].type == LexerTokenType::IntToken || token[current].type == LexerTokenType::FloatToken
            || token[current].type == LexerTokenType::VarToken)
        {
            node->type = token[current];
            current++;
        } else if (token[current].type == LexerTokenType::ParenOpen)
        {
            current++;
            std::shared_ptr<Node> left = Expression();

            if (token[current].type == LexerTokenType::ParenClose)
            {
                current++;
                return left;
            } else
            {
                // Handle error - unmatched parentheses
                throw std::runtime_error("Unbalanced parentheses");
            }
        } else
        {
            // Handle error - invalid token
            throw std::runtime_error("Invalid token");
        }

        return node;
    }

  public:
    Parser(const std::vector<LexerToken> &tokens) : token(tokens), current(0) {}

    const std::vector<std::shared_ptr<Node>> astRoot() { return compound; }

    bool Parse()
    {
        if (current >= token.size()) { return false; }

        while (current < token.size())
        {
            root = Expression();
            compound.push_back(root);
        }

        return !compound.empty();
    }
};

int main()
{
    // تعريف قائمة الرموز tokens هنا
    std::vector<LexerToken> tokens = {
        // إضافة الرموز هنا
        // يمكنك تعبئة هذه القائمة بناءً على مخرجات محلل القواعد الخاص بك
    };

    Parser parser(tokens);
 if (parser.Parse())
    {
        std::vector<std::shared_ptr<Node>> ast = parser.astRoot();
        // استخدام AST أو إجراء المزيد من العمليات
    }
    else { std::cout << "فشل في التحليل النحوي.\n"; }

    return 0;
}