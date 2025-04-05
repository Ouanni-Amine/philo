import sys
import re
from collections import defaultdict

COLORS = {
    'T': '\033[94m',
    'E': '\033[92m',
    'R': '\033[93m',
    'L': '\033[95m',
    'S': '\033[91m',
    '-': '\033[0m'
}

class PhiloVisualizer:
    def __init__(self):
        self.events = defaultdict(list)
        self.max_time = 0
        self.num_philos = 0
        self.fork_count = defaultdict(int)

    def strip_ansi_codes(self, text):
        """Remove ANSI escape sequences from text."""
        ansi_escape = re.compile(r'\x1B(?:[@-Z\\-_]|\[[0-?]*[ -/]*[@-~])')
        return ansi_escape.sub('', text)

    def parse_line(self, line):
        """Parse a line of output into a (time, philo, event) tuple."""
        match = re.match(r"(\d+)\s+(\d+)\s+(.+)", line)
        if not match:
            return None

        time = int(match.group(1))
        philo = int(match.group(2)) - 1
        action = match.group(3).strip()

        self.num_philos = max(self.num_philos, philo + 1)
        self.max_time = max(self.max_time, time)

        if "has taken a fork" in action:
            if self.fork_count[philo] == 0:
                event = 'R'
                self.fork_count[philo] = 1
            elif self.fork_count[philo] == 1:
                event = 'L'
                self.fork_count[philo] = 2
        elif "is eating" in action:
            event = 'E'
        elif "is sleeping" in action:
            event = 'S'
            self.fork_count[philo] = 0
        elif "is thinking" in action:
            event = 'T'
        else:
            return None

        return (time, philo, event)

    def display_watermark(self):
        """Display the Lomer watermark in purple."""
        purple = '\033[95m'
        reset = '\033[0m'
        watermark = [
            "    __    ____   __  ___ ______ ____ ",
            "   / /   / __ \\ /  |/  // ____// __ \\",
            "  / /   / / / // /|_/ // __/  / /_/ /",
            " / /___/ /_/ // /  / // /___ / _, _/ ",
            "/_____/\\____//_/  /_//_____//_/ |_|  "
        ]
        print(f"{purple}By:{reset}")
        for line in watermark:
            print(f"{purple}{line}{reset}")
        print()

    def display_timeline(self):
        """Display a readable timeline of philosopher activities."""
        self.display_watermark()

        print("=== Philosophers Timeline ===")
        print("Legend:")
        print(f"  {COLORS['T']}█ Thinking{COLORS['-']}  "
              f"{COLORS['E']}█ Eating{COLORS['-']}    "
              f"{COLORS['R']}█ Take Right{COLORS['-']}  "
              f"{COLORS['L']}█ Take Left{COLORS['-']}  "
              f"{COLORS['S']}█ Sleeping{COLORS['-']}")
        print("═" * 70)

        timestamps = sorted(self.events.keys())
        print("Time (ms): ", end="")
        for t in timestamps:
            print(f"{t:<10}", end="")
        print("\n" + "─" * 70)

        current_states = defaultdict(lambda: ('T', 0))
        timeline_width = len(timestamps) * 10

        for p in range(self.num_philos):
            print(f"Philo {p + 1:<2}: ", end="")
            pos = 0

            for i, t in enumerate(timestamps):
                start_pos = i * 10
                end_pos = (i + 1) * 10 - 1

                while pos < start_pos:
                    state, _ = current_states[p]
                    print(f"{COLORS[state]}█{COLORS['-']}", end="")
                    pos += 1

                if t in self.events:
                    events_at_t = [event for philo, event in self.events[t] if philo == p]
                    for event in events_at_t:
                        if pos <= end_pos:
                            print(f"{COLORS[event]}█{COLORS['-']}", end="")
                            pos += 1
                            current_states[p] = (event, t)

            while pos < timeline_width:
                state, _ = current_states[p]
                print(f"{COLORS[state]}█{COLORS['-']}", end="")
                pos += 1
            print()

        print("═" * 70)

    def process_input(self):
        """Read and process input from stdin."""
        for line in sys.stdin:
            line = self.strip_ansi_codes(line)
            if "All philosophers finished" in line or not line.strip():
                break
            result = self.parse_line(line)
            if result:
                time, philo, event = result
                self.events[time].append((philo, event))

def main():
    visualizer = PhiloVisualizer()
    visualizer.process_input()
    visualizer.display_timeline()

if __name__ == "__main__":
    main()
