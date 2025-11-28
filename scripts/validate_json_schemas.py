#!/usr/bin/env python3
"""
Script de validação de JSON Schemas para Data Tables do MyProject2.

Valida todos os arquivos JSON em Content/Data/JSON/ contra seus schemas
correspondentes em Content/Data/JSON/Schemas/.

Uso:
    python scripts/validate_json_schemas.py
    python scripts/validate_json_schemas.py --file Content/Data/JSON/RaceDataTable.json
    python scripts/validate_json_schemas.py --verbose
"""

import json
import os
import sys
from pathlib import Path
from typing import Dict, List, Tuple, Optional

try:
    import jsonschema
    from jsonschema import validate, ValidationError
except ImportError:
    print("ERRO: Biblioteca 'jsonschema' não encontrada.")
    print("Instale com: pip install jsonschema")
    sys.exit(1)


# Mapeamento de arquivos JSON para seus schemas
JSON_SCHEMA_MAP = {
    "AbilityScoreDataTable.json": "AbilityScoreDataTable.schema.json",
    "TraitDataTable.json": "TraitDataTable.schema.json",
    "LanguageDataTable.json": "LanguageDataTable.schema.json",
    "SkillDataTable.json": "SkillDataTable.schema.json",
    "SpellDataTable.json": "SpellDataTable.schema.json",
    "SpellSchoolDataTable.json": "SpellSchoolDataTable.schema.json",
    "DamageTypeDataTable.json": "DamageTypeDataTable.schema.json",
    "ConditionDataTable.json": "ConditionDataTable.schema.json",
    "ProficiencyDataTable.json": "ProficiencyDataTable.schema.json",
    "RaceDataTable.json": "RaceDataTable.schema.json",
    "ClassDataTable.json": "ClassDataTable.schema.json",
    "BackgroundDataTable.json": "BackgroundDataTable.schema.json",
    "FeatDataTable.json": "FeatDataTable.schema.json",
    "FeatureDataTable.json": "FeatureDataTable.schema.json",
    "ItemDataTable.json": "ItemDataTable.schema.json",
}


class ValidationResult:
    """Resultado de validação de um arquivo JSON."""

    def __init__(self, file_path: str, is_valid: bool, errors: List[str] = None):
        self.file_path = file_path
        self.is_valid = is_valid
        self.errors = errors or []

    def __str__(self) -> str:
        if self.is_valid:
            return f"[OK] {self.file_path}: Valido"
        else:
            error_msg = "\n".join(f"  - {error}" for error in self.errors)
            return f"[ERRO] {self.file_path}: Invalido\n{error_msg}"


def load_json_file(file_path: Path) -> Optional[Dict]:
    """Carrega um arquivo JSON."""
    try:
        with open(file_path, "r", encoding="utf-8") as f:
            return json.load(f)
    except json.JSONDecodeError as e:
        raise ValueError(f"JSON inválido: {e}")
    except FileNotFoundError:
        raise FileNotFoundError(f"Arquivo não encontrado: {file_path}")


def load_schema(schema_path: Path) -> Dict:
    """Carrega um schema JSON."""
    try:
        with open(schema_path, "r", encoding="utf-8") as f:
            return json.load(f)
    except FileNotFoundError:
        raise FileNotFoundError(f"Schema não encontrado: {schema_path}")
    except json.JSONDecodeError as e:
        raise ValueError(f"Schema JSON inválido: {e}")


def validate_json_against_schema(
    json_data: Dict, schema: Dict, file_path: str, verbose: bool = False
) -> ValidationResult:
    """Valida dados JSON contra um schema."""
    errors = []

    try:
        # Validação principal
        validate(instance=json_data, schema=schema)
        return ValidationResult(file_path, True)

    except ValidationError as e:
        # Coleta todos os erros de validação
        errors.append(f"Erro de validação: {e.message}")
        if verbose:
            errors.append(f"  Caminho: {'.'.join(str(p) for p in e.path)}")
            errors.append(f"  Schema path: {'.'.join(str(p) for p in e.schema_path)}")

        # Tenta coletar erros adicionais (se houver)
        for error in e.context:
            errors.append(f"  Erro relacionado: {error.message}")

        return ValidationResult(file_path, False, errors)

    except Exception as e:
        errors.append(f"Erro inesperado: {str(e)}")
        return ValidationResult(file_path, False, errors)


def validate_all_json_files(
    json_dir: Path, schema_dir: Path, verbose: bool = False
) -> List[ValidationResult]:
    """Valida todos os arquivos JSON contra seus schemas."""
    results = []

    for json_file, schema_file in JSON_SCHEMA_MAP.items():
        json_path = json_dir / json_file
        schema_path = schema_dir / schema_file

        # Verifica se arquivo JSON existe
        if not json_path.exists():
            results.append(
                ValidationResult(
                    str(json_path), False, [f"Arquivo JSON não encontrado: {json_file}"]
                )
            )
            continue

        # Verifica se schema existe
        if not schema_path.exists():
            results.append(
                ValidationResult(
                    str(json_path),
                    False,
                    [f"Schema não encontrado: {schema_file}"],
                )
            )
            continue

        try:
            # Carrega JSON e schema
            json_data = load_json_file(json_path)
            schema = load_schema(schema_path)

            # Valida
            result = validate_json_against_schema(
                json_data, schema, str(json_path), verbose
            )
            results.append(result)

        except Exception as e:
            results.append(
                ValidationResult(str(json_path), False, [f"Erro ao processar: {str(e)}"])
            )

    return results


def validate_single_file(
    file_path: Path, schema_dir: Path, verbose: bool = False
) -> ValidationResult:
    """Valida um único arquivo JSON."""
    json_file = file_path.name

    if json_file not in JSON_SCHEMA_MAP:
        return ValidationResult(
            str(file_path),
            False,
            [f"Arquivo não está no mapeamento de schemas: {json_file}"],
        )

    schema_file = JSON_SCHEMA_MAP[json_file]
    schema_path = schema_dir / schema_file

    if not schema_path.exists():
        return ValidationResult(
            str(file_path), False, [f"Schema não encontrado: {schema_file}"]
        )

    try:
        json_data = load_json_file(file_path)
        schema = load_schema(schema_path)
        return validate_json_against_schema(json_data, schema, str(file_path), verbose)
    except Exception as e:
        return ValidationResult(str(file_path), False, [f"Erro ao processar: {str(e)}"])


def main():
    """Função principal."""
    import argparse

    parser = argparse.ArgumentParser(
        description="Valida arquivos JSON contra seus schemas"
    )
    parser.add_argument(
        "--file",
        type=str,
        help="Valida apenas um arquivo específico (caminho relativo ou absoluto)",
    )
    parser.add_argument(
        "--verbose",
        action="store_true",
        help="Mostra informações detalhadas sobre erros",
    )
    parser.add_argument(
        "--json-dir",
        type=str,
        default="Content/Data/JSON",
        help="Diretório contendo arquivos JSON (padrão: Content/Data/JSON)",
    )
    parser.add_argument(
        "--schema-dir",
        type=str,
        default="Content/Data/JSON/Schemas",
        help="Diretório contendo schemas (padrão: Content/Data/JSON/Schemas)",
    )

    args = parser.parse_args()

    # Converte para Path
    json_dir = Path(args.json_dir)
    schema_dir = Path(args.schema_dir)

    # Valida diretórios
    if not json_dir.exists():
        print(f"[ERRO] Diretorio JSON nao encontrado: {json_dir}")
        sys.exit(1)

    if not schema_dir.exists():
        print(f"[ERRO] Diretorio de schemas nao encontrado: {schema_dir}")
        sys.exit(1)

    # Validação
    if args.file:
        # Valida arquivo único
        file_path = Path(args.file)
        if not file_path.is_absolute():
            file_path = json_dir / file_path.name

        result = validate_single_file(file_path, schema_dir, args.verbose)
        print(result)

        sys.exit(0 if result.is_valid else 1)
    else:
        # Valida todos os arquivos
        print("Validando arquivos JSON contra schemas...\n")
        results = validate_all_json_files(json_dir, schema_dir, args.verbose)

        # Mostra resultados
        valid_count = sum(1 for r in results if r.is_valid)
        total_count = len(results)

        for result in results:
            print(result)
            if not result.is_valid:
                print()  # Linha em branco após erros

        print(f"\nResumo: {valid_count}/{total_count} arquivos validos")

        # Exit code baseado em resultados
        sys.exit(0 if valid_count == total_count else 1)


if __name__ == "__main__":
    main()
