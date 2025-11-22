# Guia Rápido - Novas Regras Implementadas

## 📋 Regras Criadas

### 1. Git/Commits (`git-commits.mdc`)
### 2. Testes (`testing.mdc`)
### 3. CI/CD (`ci-cd.mdc`)

## 🚀 Como Usar

### Git/Commits

**Formato:**
```bash
<type>(<scope>): <descrição>
```

**Exemplos:**
```bash
feat(Characters): adiciona CharacterTotalLvl ao Data Asset
fix(Components): corrige busca de CharacterDataComponent
refactor(Utils): move FindCharacterDataComponent para helper
docs(Architecture): adiciona diagramas Mermaid
```

**Configurar template de commit:**
```bash
git config commit.template .gitmessage
```

### Testes

**Quando escrever:**
- ✅ Funções helper em `Utils/`
- ✅ Funções puras
- ✅ Lógica de cálculo complexa

**Estrutura:**
```
Source/MyProject2/Utils/Tests/
└── ComponentHelpersTests.cpp
```

**Exemplo:** Veja `Source/MyProject2/Utils/Tests/ComponentHelpersTests.cpp.example`

### CI/CD

**Arquivo criado:**
- `.github/workflows/build.yml`

**Nota:** GitHub Actions não tem Unreal Engine por padrão. Você precisa:
1. Usar self-hosted runner com UE instalado, OU
2. Configurar manualmente o caminho do UE no workflow

**Para ativar:**
1. Commit o arquivo `.github/workflows/build.yml`
2. Push para GitHub
3. GitHub Actions executará automaticamente

## ✅ Checklist

### Antes de Commitar

- [ ] Mensagem segue formato Conventional Commits?
- [ ] Código compila?
- [ ] Testes passam (se houver)?
- [ ] Documentação atualizada?

### Ao Criar Função Helper

- [ ] Função está em `Utils/`?
- [ ] Testes escritos?
- [ ] Casos edge cobertos (nullptr, valores inválidos)?

## 📚 Documentação Completa

- **Git/Commits**: `.cursor/rules/git-commits.mdc`
- **Testes**: `.cursor/rules/testing.mdc`
- **CI/CD**: `.cursor/rules/ci-cd.mdc`

## 🎯 Próximos Passos

1. **Git**: Configure template de commit (`git config commit.template .gitmessage`)
2. **Testes**: Implemente primeiro teste baseado no exemplo
3. **CI/CD**: Configure self-hosted runner ou ajuste workflow para seu ambiente

---

**Todas as regras estão ativas e serão aplicadas automaticamente pelo Cursor!**
