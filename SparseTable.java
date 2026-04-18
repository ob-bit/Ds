public class SparseTable {
    private int[][] st;
    private int[] log;
    private int n;

    public SparseTable(int[] arr) {
        this.n = arr.length;
        int maxLog = (int) (Math.log(n) / Math.log(2)) + 1;
        this.st = new int[n][maxLog];
        this.log = new int[n + 1];

        // 1. Precompute logarithms for O(1) query time
        for (int i = 2; i <= n; i++) {
            log[i] = log[i / 2] + 1;
        }

        // 2. Initialize the first column with the original array
        for (int i = 0; i < n; i++) {
            st[i][0] = arr[i];
        }

        // 3. Build the table bottom-up using dynamic programming
        for (int j = 1; j < maxLog; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                // Minimum of two overlapping ranges of length 2^(j-1)
                st[i][j] = Math.min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    
     // Answers range minimum query in O(1) time
     //  L start index (inclusive)
    // R end index (inclusive)
     
    public int query(int L, int R) {
        int j = log[R - L + 1];
        return Math.min(st[L][j], st[R - (1 << j) + 1][j]);
    }

    public static void main(String[] args) {
    int[] data = {47, 75, 44, 66, 95, 100, 59, 54, 2, 63, 56, 40, 8, 88, 100, 89, 38, 2, 11, 81};
    SparseTable table = new SparseTable(data);
    
    int[][] queries = {{7, 12}, {18, 18}, {13, 19}, {12, 17}, {2, 16}};
    
    for (int[] q : queries) {
        System.out.printf("Min in range [%d, %d]: %d%n", q[0], q[1], table.query(q[0], q[1]));
    }
}

