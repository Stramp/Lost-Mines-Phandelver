# 🏃 Executando Testes

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🖥️ No Editor</b></summary>

> **Método 1: Automation Tool (GUI)**
>
> 1. Abra o Editor
> 2. Menu: **Window → Developer Tools → Automation Tool**
> 3. Selecione os testes desejados
> 4. Clique em **Start Tests**
>
> **Método 2: Linha de Comando (Terminal)**
>
> **Comando oficial da Epic Games:**
>
> ```batch
> UnrealEditor-Cmd.exe "F:\UNREAL GAME\MyProject2\MyProject2.uproject" ^
> -ExecCmds="Automation RunTests MyProject2" ^
> -unattended ^
> -nopause ^
> -nullrhi ^
> -NoSound ^
> -NoSplash ^
> -testexit="Automation Test Queue Empty" ^
> -log ^
> -stdout
> ```
>
> **Scripts do projeto:**
>
> ```bash
> # Todos os testes
> run_tests.bat
>
> # Teste específico
> run_tests.bat MyProject2.Data.Tables.FeatDataTable
>
> # Versão rápida otimizada
> run_tests_quick.bat
> ```
>
> **Nota:** A inicialização do Unreal Engine pode levar 1-2 minutos. Isso é normal.
>
> **Referência:** [Write C++ Tests](https://dev.epicgames.com/documentation/en-us/unreal-engine/write-cplusplus-tests-in-unreal-engine)

</details>

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔄 CI/CD</b></summary>

> **Integração com GitHub Actions:**
>
> ```yaml
> - name: Run Tests
> run: |
> "C:\Program Files\Epic Games\UE_5.7\Engine\Binaries\Win64\UnrealEditor-Cmd.exe"
> "F:\UNREAL GAME\MyProject2\MyProject2.uproject"
> -ExecCmds="Automation RunTests MyProject2"
> -unattended
> -nopause
> -nullrhi
> -NoSound
> -NoSplash
> -testexit="Automation Test Queue Empty"
> -log
> -stdout
> ```

</details>

---

## 🔗 Navegação

- [📚 Guia de Testes - Índice](./index.md)
- [📝 Nomenclatura de Testes](./nomenclatura.md)

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Documentação inicial extraída de testing.md |
