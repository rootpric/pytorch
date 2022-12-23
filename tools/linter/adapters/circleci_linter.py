"""
Checks that the configuration in .circleci/config.yml has been properly regenerated.
"""

import os
import argparse
import subprocess
import sys
import logging
import time
from enum import Enum
from typing import List, NamedTuple, Optional
import json


CHECKED_IN_FILE = "config.yml"
REGENERATION_SCRIPT = "regenerate.sh"

PARENT_DIR = os.path.basename(os.path.dirname(os.path.abspath(__file__)))
README_PATH = os.path.join(PARENT_DIR, "README.md")


class LintSeverity(str, Enum):
    ERROR = "error"
    WARNING = "warning"
    ADVICE = "advice"
    DISABLED = "disabled"


class LintMessage(NamedTuple):
    path: Optional[str]
    line: Optional[int]
    char: Optional[int]
    code: str
    severity: LintSeverity
    name: str
    original: Optional[str]
    replacement: Optional[str]
    description: Optional[str]


IS_WINDOWS: bool = os.name == "nt"


def as_posix(name: str) -> str:
    return name.replace("\\", "/") if IS_WINDOWS else name


def run_command(args: List[str], cwd: str) -> "subprocess.CompletedProcess[bytes]":
    logging.debug("$ %s", " ".join(args))
    start_time = time.monotonic()
    try:
        return subprocess.run(
            args,
            cwd=cwd,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            check=True,
        )
    finally:
        end_time = time.monotonic()
        logging.debug("took %dms", (end_time - start_time) * 1000)


def run_check(
    regen_script_working_dir: str, regen_script: str, config_file: str
) -> List[LintMessage]:
    try:
        proc = run_command(["python3", regen_script], regen_script_working_dir)
    except Exception as err:
        return [
            LintMessage(
                path=None,
                line=None,
                char=None,
                code="CIRCLECI",
                severity=LintSeverity.ERROR,
                name="command-failed",
                original=None,
                replacement=None,
                description=(
                    f"Failed due to {err.__class__.__name__}:\n{err}"
                    if not isinstance(err, subprocess.CalledProcessError)
                    else (
                        "COMMAND (exit code {returncode})\n"
                        "{command}\n\n"
                        "STDERR\n{stderr}\n\n"
                        "STDOUT\n{stdout}"
                    ).format(
                        returncode=err.returncode,
                        command=" ".join(as_posix(x) for x in err.cmd),
                        stderr=err.stderr.decode("utf-8").strip() or "(empty)",
                        stdout=err.stdout.decode("utf-8").strip() or "(empty)",
                    )
                ),
            )
        ]

    with open(config_file, mode="rb") as f:
        config = f.read()
    if proc.stdout == config:
        return []

    return [
        LintMessage(
            path=config_file,
            line=None,
            char=None,
            code="CIRCLECI",
            severity=LintSeverity.ERROR,
            name="config inconsistency",
            original=config.decode("utf-8"),
            replacement=proc.stdout.decode("utf-8"),
            description=(
                "The checked-in CircleCI config.yml file does not match what was generated by the scripts. "
                "Re-run with '-a' to accept changes."
            ),
        )
    ]


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="circleci consistency linter",
        fromfile_prefix_chars="@",
    )
    parser.add_argument(
        "--config-yml",
        required=True,
        help="location of config.yml",
    )
    parser.add_argument(
        "--regen-script-working-dir",
        required=True,
        help="this script will chdir to this argument before running --regen-script",
    )
    parser.add_argument(
        "--regen-script",
        required=True,
        help="location of the config generation script, relative to --regen-script-working-dir",
    )
    parser.add_argument(
        "--verbose",
        action="store_true",
        help="verbose logging",
    )

    args = parser.parse_args()

    logging.basicConfig(
        format="<%(threadName)s:%(levelname)s> %(message)s",
        level=logging.NOTSET if args.verbose else logging.DEBUG,
        stream=sys.stderr,
    )

    for lint_message in run_check(
        args.regen_script_working_dir, args.regen_script, args.config_yml
    ):
        print(json.dumps(lint_message._asdict()), flush=True)
