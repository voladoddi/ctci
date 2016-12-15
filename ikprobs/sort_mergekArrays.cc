/*
 * Complete the function below.
 */
void mergeTwoArrays(const vector<int>&first,const vector<int> &second, vector<int> &result)
{
    // [-PROBLEM-] result has to start from beginning every time, which is not difficult per se, but
    // insert is a costly operation in result if it's a vector.
    
    // And this approach requires to compare result elements with the result itself,
    // probably not a good approach.
    
    
    
}
void mergeKarrays(vector<vector<int> >&iarray, vector<int> &result)
{
    // [-PROBLEM-] The complexity of this is increasing.
    // First iteration - this is going to be O(N)
    // Thereby for every iteration, it's going to be (k-1)*O(2N) + (k-2)*O(3N) + ... (1)*O((k-1)N)
    if(result.empty())
    {
        mergeTwoarrays(iarray[iarray.size()-1],iarray[iarray.size()-2], result);
        iarray.pop_back();
        iarray.pop_back();
    }
    else
        for(int k = iarray.size()-1; k > 0; k-=1)
        {
            mergeTwoarrays
        }
    
    
}

}
vector < int > mergearrays(vector < vector < int > > iarray)
{
    int k = iarray.size();
    int n = iarray[0].size();
    vector<int> result;
    mergeKarrays(iarray, result);
    
}

