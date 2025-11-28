---
title: "Setup Completo"
category: technical
subcategory: guides
tags: [setup, installation, configuration, environment]
last_updated: 2024-12-27
difficulty: beginner
related: [getting-started.md, data-tables-setup.md]
---

**Navegação:** [Home](../../../README.md) > [Documentação](index.md) > [Técnico](../technical/index.md) > [Guias](guides/index.md) > Setup

# Guia de Setup Completo - MyProject2

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Visão Geral</b></summary>

> Este guia fornece instruções passo a passo para configurar o ambiente de desenvolvimento do projeto MyProject2 do zero, permitindo replicar completamente o projeto.

</details>

---

## 🔧 Pré-requisitos

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🛠️ Ferramentas Necessárias</b></summary>

> **Requisitos obrigatórios:**
>
> - **Unreal Engine 5.7** - Instalado via Epic Games Launcher
> - **Visual Studio 2022** - Com componentes C++ (Desktop development with C++)
> - **Windows 10/11** - Plataforma Win64
> - **Git** - Para clonar o repositório
>
> **Requisitos opcionais (recomendados):**
>
> - **Cursor/VS Code** - IDE recomendada para desenvolvimento
> - **LLVM/clangd** - Para autocomplete e linting (opcional)

</details>

---

## 📥 Passo 1: Clonar o Repositório

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📂 Obter o Código</b></summary>

> ```bash
> # Clonar o repositório
> git clone <repository-url>
> cd MyProject2
> ```
>
> **Nota:** Substitua `<repository-url>` pela URL real do repositório Git.

</details>

---

## 🎮 Passo 2: Instalar Unreal Engine 5.7

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⚙️ Configurar Unreal Engine</b></summary>

> ### 2.1 Instalar via Epic Games Launcher
>
> 1. Abra o **Epic Games Launcher**
> 2. Vá em **Unreal Engine** → **Library**
> 3. Clique em **+ Add Version**
> 4. Selecione **5.7** e instale
> 5. Aguarde a instalação completa
>
> ### 2.2 Verificar Instalação
>
> O Unreal Engine 5.7 deve estar instalado em:
>
> ```
> C:\Program Files\Epic Games\UE_5.7
> ```
>
> **Nota:** Se instalado em outro local, anote o caminho - você precisará dele depois.
>
> ### 2.3 Verificar Componentes C++
>
> Certifique-se de que o Visual Studio 2022 está instalado com componentes C++:
>
> 1. Abra **Visual Studio Installer**
> 2. Clique em **Modify** no Visual Studio 2022
> 3. Verifique se **Desktop development with C++** está marcado
> 4. Se não estiver, marque e instale

</details>

---

## 🔨 Passo 3: Gerar Arquivos do Projeto

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📝 Criar Arquivos de Build</b></summary>

> ### 3.1 Descobrir Caminhos
>
> Antes de gerar os arquivos, você precisa descobrir:
>
> 1. **Caminho do Unreal Engine 5.7:**
>    - Geralmente: `C:\Program Files\Epic Games\UE_5.7`
>    - Ou verifique no Epic Games Launcher → Unreal Engine → Library
>
> 2. **Caminho do Projeto:**
>    - O caminho completo onde você clonou o repositório
>    - Exemplo: `F:\UNREAL GAME\MyProject2`
>
> ### 3.2 Gerar Arquivos (Método 1: Unreal Editor)
>
> **Recomendado para primeira vez:**
>
> 1. Navegue até a pasta do projeto
> 2. Clique duas vezes em `MyProject2.uproject`
> 3. Selecione **"Generate Visual Studio project files"** quando solicitado
> 4. Aguarde a geração
>
> ### 3.3 Gerar Arquivos (Método 2: Linha de Comando)
>
> **Para gerar via terminal:**
>
> ```bash
> # Substitua os caminhos pelos seus
> "C:\Program Files\Epic Games\UE_5.7\Engine\Build\BatchFiles\RunUBT.bat" ^
>     -projectfiles ^
>     -project="F:\UNREAL GAME\MyProject2\MyProject2.uproject" ^
>     -game ^
>     -engine
> ```
>
> **Variáveis de ambiente (opcional):**
>
> Você pode criar variáveis de ambiente para facilitar:
>
> - `UE_ROOT` = `C:\Program Files\Epic Games\UE_5.7`
> - `PROJECT_ROOT` = `F:\UNREAL GAME\MyProject2`
>
> Então use:
>
> ```bash
> "%UE_ROOT%\Engine\Build\BatchFiles\RunUBT.bat" ^
>     -projectfiles ^
>     -project="%PROJECT_ROOT%\MyProject2.uproject" ^
>     -game ^
>     -engine
> ```

</details>

---

## 🏗️ Passo 4: Compilar o Projeto

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⚙️ Build do Projeto</b></summary>

> ### 4.1 Compilar no Unreal Editor (Recomendado)
>
> 1. Abra `MyProject2.uproject` (duplo clique)
> 2. O editor compilará automaticamente na primeira vez
> 3. Aguarde a compilação completa
>
> **Nota:** A primeira compilação pode levar 5-15 minutos dependendo do hardware.
>
> ### 4.2 Compilar no Cursor/VS Code
>
> 1. Abra o workspace: `File → Open Workspace from File → MyProject2.code-workspace`
> 2. Pressione `Ctrl+Shift+P`
> 3. Digite: `Tasks: Run Task`
> 4. Selecione: **"MyProject2Editor Win64 Development Build"**
> 5. Aguarde a compilação
>
> ### 4.3 Compilar via Linha de Comando
>
> ```bash
> # Substitua os caminhos pelos seus
> "C:\Program Files\Epic Games\UE_5.7\Engine\Build\BatchFiles\Build.bat" ^
>     MyProject2Editor ^
>     Win64 ^
>     Development ^
>     "F:\UNREAL GAME\MyProject2\MyProject2.uproject" ^
>     -waitmutex
> ```

</details>

---

## ✅ Passo 5: Verificar Instalação

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔍 Validar Setup</b></summary>

> ### 5.1 Verificar Compilação
>
> Após compilar, verifique se os arquivos foram gerados:
>
> ```
> MyProject2/
> ├── Binaries/
> │   └── Win64/
> │       └── UnrealEditor-MyProject2.dll  ← Deve existir
> └── Intermediate/
>     └── Build/
>         └── Win64/
>             └── UnrealEditor/
>                 └── Development/
>                     └── MyProject2Editor.target.cs  ← Deve existir
> ```
>
> ### 5.2 Verificar no Editor
>
> 1. Abra o projeto no Unreal Editor
> 2. Verifique se não há erros no **Output Log**
> 3. Tente criar um Actor e adicionar componentes:
>    - `CharacterDataComponent`
>    - `CharacterSheetComponent`
>
> ### 5.3 Executar Testes
>
> Para verificar se tudo está funcionando:
>
> 1. No Editor: **Window → Developer Tools → Automation Tool**
> 2. Filtre por `MyProject2`
> 3. Execute alguns testes unitários
> 4. Se os testes aparecerem e executarem, o setup está correto! ✅

</details>

---

## 📚 Passo 6: Configurar Data Tables

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🗂️ Preparar Dados do Sistema</b></summary>

> **Importante:** Antes de criar personagens, você precisa configurar os Data Tables.
>
> **📖 Para instruções completas, veja [docs/technical/guides/data-tables-setup.md](data-tables-setup.md)**
>
> **Resumo rápido:**
>
> 1. Crie Data Tables no Content Browser:
>    - Race Data Table
>    - Class Data Table
>    - Background Data Table
>    - Feat Data Table
>
> 2. Configure a estrutura de cada Data Table conforme a documentação
>
> 3. Preencha com dados válidos (exemplos na documentação)

</details>

---

## 🐛 Troubleshooting

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>❓ Problemas Comuns</b></summary>

> ### Problema: "Cannot find Unreal Engine"
>
> **Solução:**
>
> 1. Verifique se o Unreal Engine 5.7 está instalado
> 2. Verifique o caminho de instalação
> 3. Tente abrir o projeto pelo Epic Games Launcher
>
> ### Problema: Erro de Compilação
>
> **Solução:**
>
> 1. Verifique se Visual Studio 2022 está instalado com componentes C++
> 2. Feche o Editor completamente
> 3. Delete as pastas `Binaries/` e `Intermediate/`
> 4. Regenere os arquivos do projeto
> 5. Recompile
>
> ### Problema: Testes não aparecem
>
> **Solução:**
>
> 1. Verifique se o projeto compilou com sucesso
> 2. Verifique se os arquivos de teste estão no projeto
> 3. Recompile o projeto
> 4. Reinicie o Editor
>
> ### Problema: Caminhos hardcoded não funcionam
>
> **Solução:**
>
> 1. Todos os caminhos no README são exemplos
> 2. Substitua pelos seus caminhos reais
> 3. Use variáveis de ambiente se preferir
>
> **📖 Para mais troubleshooting, veja [docs/technical/guides/troubleshooting.md](troubleshooting.md)**

</details>

---

## ✅ Checklist de Setup

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Verificação Final</b></summary>

> Antes de considerar o setup completo, verifique:
>
> - [ ] Unreal Engine 5.7 instalado e funcionando
> - [ ] Visual Studio 2022 com componentes C++ instalado
> - [ ] Projeto clonado do repositório
> - [ ] Arquivos do projeto gerados (`.sln`, `.vcxproj`)
> - [ ] Projeto compila sem erros
> - [ ] Editor abre sem erros
> - [ ] Testes aparecem no Automation Tool
> - [ ] Data Tables configurados (se necessário)
>
> **Se todos os itens estão marcados, o setup está completo! ✅**

</details>

---

## 🚀 Próximos Passos

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📖 Continuar Desenvolvimento</b></summary>

> Após completar o setup:
>
> 1. **Leia o [Guia de Início Rápido](getting-started.md)** - Criar primeiro personagem
> 2. **Configure Data Tables** - [Guia de Data Tables](data-tables-setup.md)
> 3. **Explore a Arquitetura** - [ARCHITECTURE.md](../../../ARCHITECTURE.md)
> 4. **Execute Testes** - [Guia de Testes](testing.md)
>
> **📖 Para documentação completa, veja [docs/index.md](../../index.md)**

</details>
